#!/bin/bash

# Script pour tester la médiane du nombre d'opérations

echo "╔════════════════════════════════════════════════════════╗"
echo "║     Test de médiane du nombre d'opérations             ║"
echo "╚════════════════════════════════════════════════════════╝"

# Fonction pour générer des nombres aléatoires uniques
generate_numbers() {
    local count=$1
    local max=$((count * 10))
    local numbers=()

    while [ ${#numbers[@]} -lt $count ]; do
        num=$((RANDOM % max))
        # Vérifie si le nombre n'est pas déjà dans le tableau
        if [[ ! " ${numbers[@]} " =~ " ${num} " ]]; then
            numbers+=($num)
        fi
    done

    echo "${numbers[@]}"
}

# Fonction pour calculer la médiane
calculate_median() {
    local arr=("$@")
    local sorted=($(printf '%s\n' "${arr[@]}" | sort -n))
    local count=${#sorted[@]}

    if [ $((count % 2)) -eq 0 ]; then
        local mid1=$((count / 2 - 1))
        local mid2=$((count / 2))
        echo "scale=1; (${sorted[$mid1]} + ${sorted[$mid2]}) / 2" | bc
    else
        local mid=$((count / 2))
        echo "${sorted[$mid]}"
    fi
}

# Fonction pour tester une taille donnée
test_size() {
    local size=$1
    local iterations=$2
    local results=()
	local max_op=$3
	local min_op=$4

    echo ""
    echo "=== Test avec $size nombres ($iterations itérations) ==="

    for ((i=1; i<=$iterations; i++)); do
        # Génère des nombres aléatoires
        numbers=$(generate_numbers $size)

        # Exécute push_swap et compte les opérations
        ops=$(./push_swap $numbers | wc -l)
        results+=($ops)

        # Affiche la progression tous les 10 tests
        if [ $((i % 10)) -eq 0 ]; then
            echo -ne "  Progression: $i/$iterations\r"
        fi
    done

    echo -ne "\033[K"  # Efface la ligne de progression

    # Trie les résultats
    sorted_results=($(printf '%s\n' "${results[@]}" | sort -n))

    # Calcule min, max et médiane
    min=${sorted_results[0]}
    max=${sorted_results[-1]}
    median=$(calculate_median "${results[@]}")

    # Calcule la moyenne
    sum=0
    for val in "${results[@]}"; do
        sum=$((sum + val))
    done
    avg=$(echo "scale=1; $sum / ${#results[@]}" | bc)

    echo "Nombre d'opérations:"
    echo "  Min:     $min"
    echo "  Médiane: $median"
    echo "  Moyenne: $avg"
    echo "  Max:     $max"
	echo "  OP100% : $max_op"
	echo "  OP 80% : $min_op"
}

# Vérifie que push_swap existe
if [ ! -f "./push_swap" ]; then
    echo "Erreur: push_swap n'existe pas. Compilez-le d'abord avec 'make'."
    exit 1
fi

# Lance les tests
test_size 3 200 3
test_size 5 200 12
test_size 100 200 700 1500
test_size 500 100 5500 11500

# Test des fuites mémoire avec valgrind
echo ""
echo "╔════════════════════════════════════════════════════════╗"
echo "║     Test des fuites mémoire avec Valgrind              ║"
echo "╚════════════════════════════════════════════════════════╝"
echo ""

numbers=$(generate_numbers 1)
echo "Test avec 1 nombres aléatoires..."
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --error-exitcode=1 ./push_swap $numbers > /dev/null 2>&1

if [ $? -eq 0 ]; then
    echo "✓ Aucune fuite mémoire détectée!"
else
    echo "✗ Des fuites mémoire ont été détectées. Exécutez manuellement pour plus de détails:"
    echo "  valgrind --leak-check=full ./push_swap $numbers"
fi

numbers=$(generate_numbers 5)
echo "Test avec 5 nombres aléatoires..."
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --error-exitcode=1 ./push_swap $numbers > /dev/null 2>&1

if [ $? -eq 0 ]; then
    echo "✓ Aucune fuite mémoire détectée!"
else
    echo "✗ Des fuites mémoire ont été détectées. Exécutez manuellement pour plus de détails:"
    echo "  valgrind --leak-check=full ./push_swap $numbers"
fi

numbers=$(generate_numbers 100)
echo "Test avec 100 nombres aléatoires..."
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --error-exitcode=1 ./push_swap $numbers > /dev/null 2>&1

if [ $? -eq 0 ]; then
    echo "✓ Aucune fuite mémoire détectée!"
else
    echo "✗ Des fuites mémoire ont été détectées. Exécutez manuellement pour plus de détails:"
    echo "  valgrind --leak-check=full ./push_swap $numbers"
fi
numbers=$(generate_numbers 500)
echo "Test avec 500 nombres aléatoires..."
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --error-exitcode=1 ./push_swap $numbers > /dev/null 2>&1

if [ $? -eq 0 ]; then
    echo "✓ Aucune fuite mémoire détectée!"
else
    echo "✗ Des fuites mémoire ont été détectées. Exécutez manuellement pour plus de détails:"
    echo "  valgrind --leak-check=full ./push_swap $numbers"
fi


echo "Test avec "42"..."
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --error-exitcode=1 ./push_swap "42" > /dev/null 2>&1

if [ $? -eq 0 ]; then
    echo "✓ Aucune fuite mémoire détectée!"
else
    echo "✗ Des fuites mémoire ont été détectées. Exécutez manuellement pour plus de détails:"
    echo "  valgrind --leak-check=full ./push_swap "42""
fi


echo "Test avec " 1 2 3"..."
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --error-exitcode=1 ./push_swap " 1 2 3" > /dev/null 2>&1

if [ $? -eq 0 ]; then
    echo "✓ Aucune fuite mémoire détectée!"
else
    echo "✗ Des fuites mémoire ont été détectées. Exécutez manuellement pour plus de détails:"
    echo "  valgrind --leak-check=full ./push_swap " 1 2 3""
fi

echo ""
echo "✓ Tests terminés!"
