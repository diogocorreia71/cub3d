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
    valgrind --leak-check=full ./cub3D "$map_file" &> "$log_file"
    
    if [ $? -ne 0 ]; then
        echo "Falha encontrada no arquivo: $map_file"
        echo "==== Falha no arquivo: $map_file ====" >> "$LOG_FILE"
        cat "$log_file" >> "$LOG_FILE"
        echo -e "\n\n" >> "$LOG_FILE"
    else
        rm "$log_file"
    fi
}

# Executa valgrind em todos os arquivos inválidos
for map_file in "$INVALID_DIR"/*.cub; do
    run_valgrind "$map_file" "valgrind_log_invalid.txt"
done
# Executa valgrind em todos os arquivos válidos
for map_file in "$VALID_DIR"/*.cub; do
    run_valgrind "$map_file" "valgrind_log_valid.txt"
done


echo "Execução completa. Verifique o arquivo $LOG_FILE para detalhes de falhas."
Collapse










