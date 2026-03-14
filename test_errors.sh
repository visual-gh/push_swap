#!/bin/zsh
set -uo pipefail

echo "📋 TEST COMPLET DES CAS D'ERREUR (Valgrind)\n"

tests=(
    "1 2 3 2 5:Doublons"
    "1 abc 3:Caractères invalides"
    "2147483648:Overflow (>INT_MAX)"
    "-2147483649:Underflow (<INT_MIN)"
    "\"3 2 1 2\":String avec doublons"
    "\"1 abc 3\":String avec lettres"
    "\"\":String vide"
    "++5:Double signe"
    "\"1  2   3\":Espaces multiples"
    "1 2 3a 4:Mix valide/invalide"
    "\"   \":Seulement espaces"
    "\"+0 -0\":mix 0"
)

passed=0
failed=0
idx=0

# Ensure binary is built
if [[ ! -x ./push_swap ]]; then
    echo "Binaire ./push_swap introuvable — compilation via make..."
    if ! make -s; then
        echo "Échec de la compilation. Abandon." >&2
        exit 1
    fi
fi

num_tests=${#tests[@]}
for ((j=1; j<=num_tests; j++)); do
    idx=$j
    test="${tests[j]}"
    args="${test%%:*}"
    desc="${test##*:}"
    echo "🧪 Test #$idx : $desc"
    echo "   Args: $args"

    out_file="/tmp/push_swap_out_${idx}.txt"
    vg_log="/tmp/valgrind_push_swap_${idx}.log"

    # Run under Valgrind and capture program output separately
    # Use eval so quoted test args are preserved
    if ! eval "valgrind --leak-check=full --show-leak-kinds=all --errors-for-leak-kinds=all --log-file=$vg_log ./push_swap $args >$out_file 2>&1"; then
        prog_exit=$?
    else
        prog_exit=0
    fi

    output=$(cat "$out_file" 2>/dev/null || true)
    vg_summary=$(grep -E "definitely lost:|ERROR SUMMARY:" "$vg_log" 2>/dev/null || true)

    if [[ -n "$output" ]]; then
        echo "   Programme output:"
        echo "   -----"
        echo "$(sed -n '1,6p' $out_file)" | sed 's/^/   /'
        echo "   -----"
    fi

    # Determine leak status: accept several Valgrind patterns that mean "no leaks"
    # (different Valgrind versions / options can print different lines)
    if grep -q -E "definitely lost: 0 bytes in 0 blocks|All heap blocks were freed|in use at exit: 0 bytes in 0 blocks" "$vg_log" >/dev/null 2>&1; then
        lost_zero=yes
    else
        lost_zero=no
    fi

    if grep -q "ERROR SUMMARY: 0 errors" "$vg_log" >/dev/null 2>&1; then
        err_zero=yes
    else
        err_zero=no
    fi

    if [[ "$lost_zero" == "yes" && "$err_zero" == "yes" ]]; then
        echo "   ✅ Aucun leak détecté (Valgrind)"
        ((passed++))
    else
        echo "   ❌ LEAK/ERR détecté par Valgrind"
        echo "   Valgrind summary:"
        echo "$(echo "$vg_summary" | sed 's/^/   /')"
        echo "   (fichier: $vg_log)\n"
        ((failed++))
    fi
    echo "--- FIN ITERATION $idx ---"
done

echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
echo "📊 RÉSULTATS: $passed/$((passed+failed)) tests sans leaks"
if [[ $failed -eq 0 ]]; then
    echo "✅ TOUS LES TESTS PASSÉS !"
else
    echo "❌ $failed test(s) avec des leaks — voir /tmp/valgrind_push_swap_*.log"
fi

exit $failed
