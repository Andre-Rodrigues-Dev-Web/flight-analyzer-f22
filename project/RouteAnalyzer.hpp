#ifndef ROUTE_ANALYZER_HPP
#define ROUTE_ANALYZER_HPP

#include <vector>
#include <unordered_map>
#include <queue>
#include <limits>
#include <string>
#include <algorithm>
#include <utility>

namespace RouteAnalyzer {

// Estrutura para representar um nó (ponto de interesse)
// Pode incluir coordenadas para cálculos mais sofisticados (ex: distância euclidiana)
struct Node {
    std::string id;
    double x, y; // Coordenadas (opcional)
    Node(const std::string& id, double x = 0.0, double y = 0.0) : id(id), x(x), y(y) {}
};

// Estrutura para representar uma aresta (conexão entre dois nós) com um custo associado
struct Edge {
    std::string from;
    std::string to;
    double cost;
    Edge(const std::string& from, const std::string& to, double cost) : from(from), to(to), cost(cost) {}
};

class Graph {
private:
    // Lista de adjacência: mapeia cada nó para um vetor de pares (nó vizinho, custo da aresta)
    std::unordered_map<std::string, std::vector<std::pair<std::string, double>>> adjList;
    
public:
    Graph() {}

    // Adiciona uma aresta no grafo (poderia ser bidirecional se necessário)
    void addEdge(const std::string& from, const std::string& to, double cost) {
        adjList[from].push_back({to, cost});
        // Se a rota for bidirecional, descomente a linha a seguir:
        // adjList[to].push_back({from, cost});
    }

    // Algoritmo de Dijkstra para encontrar a melhor rota (menor custo) de 'start' até 'destination'
    // Retorna um par contendo o custo total e um vetor com o caminho (sequência de nós)
    std::pair<double, std::vector<std::string>> findBestRoute(const std::string& start, const std::string& destination) {
        std::unordered_map<std::string, double> distances;
        std::unordered_map<std::string, std::string> previous;
        
        // Inicializa as distâncias com infinito para todos os nós conhecidos
        for (const auto& kv : adjList) {
            distances[kv.first] = std::numeric_limits<double>::infinity();
        }
        distances[start] = 0.0;

        // Fila de prioridade para selecionar o nó com menor custo atual
        using PQElement = std::pair<double, std::string>; // (custo, id do nó)
        std::priority_queue<PQElement, std::vector<PQElement>, std::greater<PQElement>> pq;
        pq.push({0.0, start});

        while (!pq.empty()) {
            auto [cost, node] = pq.top();
            pq.pop();

            if (node == destination) break; // Destino alcançado

            if (cost > distances[node])
                continue;

            // Explora os vizinhos do nó atual
            for (auto& [neighbor, edgeCost] : adjList[node]) {
                double newCost = cost + edgeCost;
                if (newCost < distances[neighbor]) {
                    distances[neighbor] = newCost;
                    previous[neighbor] = node;
                    pq.push({newCost, neighbor});
                }
            }
        }

        std::vector<std::string> path;
        // Caso não haja rota disponível, retorna caminho vazio e custo infinito
        if (distances[destination] == std::numeric_limits<double>::infinity()) {
            return {distances[destination], path};
        }

        // Reconstrói o caminho a partir do destino até o início
        for (std::string at = destination; at != start; at = previous[at]) {
            path.push_back(at);
        }
        path.push_back(start);
        std::reverse(path.begin(), path.end());

        return {distances[destination], path};
    }
};

} // namespace RouteAnalyzer

#endif // ROUTE_ANALYZER_HPP
