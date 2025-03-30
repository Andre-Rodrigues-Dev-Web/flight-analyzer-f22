#include <iostream>
#include "RouteAnalyzer.hpp"

int main() {
    RouteAnalyzer::Graph graph;
    
    // Adicionando arestas que representam segmentos de rota
    // Exemplo: do ponto de partida "F22" para waypoints, aeroporto e porta-aviões
    graph.addEdge("F22", "Waypoint1", 100);
    graph.addEdge("Waypoint1", "Airport", 150);
    graph.addEdge("F22", "Waypoint2", 120);
    graph.addEdge("Waypoint2", "Carrier", 130);
    graph.addEdge("Waypoint1", "Carrier", 200);
    
    // Rota do F22 até o aeroporto
    auto [costAirport, routeAirport] = graph.findBestRoute("F22", "Airport");
    if (costAirport == std::numeric_limits<double>::infinity()) {
        std::cout << "Não há rota disponível para o aeroporto." << std::endl;
    } else {
        std::cout << "Melhor rota para o aeroporto (custo: " << costAirport << "): ";
        for (const auto& node : routeAirport) {
            std::cout << node << " ";
        }
        std::cout << std::endl;
    }

    // Rota do F22 até o porta-aviões
    auto [costCarrier, routeCarrier] = graph.findBestRoute("F22", "Carrier");
    if (costCarrier == std::numeric_limits<double>::infinity()) {
        std::cout << "Não há rota disponível para o porta-aviões." << std::endl;
    } else {
        std::cout << "Melhor rota para o porta-aviões (custo: " << costCarrier << "): ";
        for (const auto& node : routeCarrier) {
            std::cout << node << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
