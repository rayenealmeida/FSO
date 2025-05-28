#include <iostream>
#include <queue>
#include <vector>

struct Tarefa {
    int identificador;
    int duracao_total;
    int tempo_faltante;
    long long instante_finalizacao;

    Tarefa(int id, int duracao) 
        : identificador(id), duracao_total(duracao), 
          tempo_faltante(duracao), instante_finalizacao(0) {}
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int num_tarefas, quantum;
    std::cin >> num_tarefas >> quantum;

    std::queue<Tarefa> fila_execucao;

    for (int i = 0; i < num_tarefas; ++i) {
        int id, tempo;
        std::cin >> id >> tempo;
        fila_execucao.emplace(id, tempo * 1000); 
    }

    long long tempo_corrente = 0;
    std::vector<Tarefa> concluidas;

    while (!fila_execucao.empty()) {
        Tarefa atual = fila_execucao.front();
        fila_execucao.pop();

        int tempo_executado = std::min(atual.tempo_faltante, quantum);

        tempo_corrente += tempo_executado;
        atual.tempo_faltante -= tempo_executado;

        if (atual.tempo_faltante == 0) {
            atual.instante_finalizacao = tempo_corrente;
            concluidas.push_back(atual);
        } else {
            fila_execucao.push(atual);
        }
    }

    for (const auto& tarefa : concluidas) {
        std::cout << tarefa.identificador << " (" 
                  << tarefa.instante_finalizacao << ")\n";
    }

    return 0;
}