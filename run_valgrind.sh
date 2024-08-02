#!/bin/bash

# Diretórios com os arquivos de mapa
VALID_DIR="map_files/valid"
INVALID_DIR="map_files/invalid"

# Arquivo de log para registrar as falhas
LOG_FILE="valgrind_failures.log"

# Limpa o arquivo de log anterior, se existir
> "$LOG_FILE"

# Função para executar valgrind e verificar falhas
run_valgrind() {
    local map_file=$1
    local log_file=$2
    
    echo "Executando valgrind no arquivo: $map_file"
    output=$(valgrind --leak-check=full ./cub3D "$map_file" 2>&1)
    
    if echo "$output" | grep -q "All heap blocks were freed -- no leaks are possible"; then
        echo -e "\e[32mOK\e[0m" # Mensagem em verde
    else
        echo -e "\e[31mMapa com leaks!\e[0m" # Mensagem em vermelho
    fi
}

run() {
    ./cub3D "$map_file"
}

# Executa valgrind em todos os arquivos inválidos
for map_file in "$INVALID_DIR"/*.cub; do
    run_valgrind "$map_file" "valgrind_log_invalid.txt"
    run
done
# Executa valgrind em todos os arquivos válidos
for map_file in "$VALID_DIR"/*.cub; do
    run_valgrind "$map_file" "valgrind_log_valid.txt"
    run
done


echo "Execução completa. Verifique o arquivo $LOG_FILE para detalhes de falhas."
Collapse










