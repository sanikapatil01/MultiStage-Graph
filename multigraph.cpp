#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to;
    double base_cost;
    double cur_cost;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

   

    int S;

    cout << "Enter number of stages: ";
    cin >> S;

    if (S < 2) {
        cout << "Error: Number of stages must be at least 2.\n";
        return 0;
    }

   

    vector<int> stage_count(S);
    int N = 0;

    cout << "Enter number of nodes in each stage ("
         << S << " values): ";

    for (int i = 0; i < S; i++) {
        cin >> stage_count[i];

        if (stage_count[i] <= 0) {
            cout << "Error: Number of nodes in a stage must be positive.\n";
            return 0;
        }

        N += stage_count[i];
    }



    vector<int> stage_start(S);

    int idx = 0;

    for (int i = 0; i < S; i++) {
        stage_start[i] = idx;
        idx += stage_count[i];
    }

    

    int M;

    cout << "Enter number of edges: ";
    cin >> M;

    if (M < 0) {
        cout << "Error: Number of edges cannot be negative.\n";
        return 0;
    }

    vector<vector<Edge>> adj(N);

    cout << "\nEnter each edge as: u v cost\n";

    for (int i = 0; i < M; i++) {

        int u, v;
        double cost;

        cin >> u >> v >> cost;

        // Validate node IDs
        if (u < 0 || u >= N || v < 0 || v >= N) {
            cout << "Error: Invalid node ID in edge "
                 << u << " -> " << v << "\n";
            return 0;
        }

        if (cost < 0) {
            cout << "Error: Edge cost cannot be negative.\n";
            return 0;
        }

        Edge e;
        e.to = v;
        e.base_cost = cost;
        e.cur_cost = cost;

        adj[u].push_back(e);
    }

    

    vector<int> node_stage(N);

    for (int st = 0; st < S; st++) {
        for (int k = 0; k < stage_count[st]; k++) {
            int node = stage_start[st] + k;
            node_stage[node] = st;
        }
    }



    const double INF = 1e30;

    vector<double> best_cost(N, INF);
    vector<int> next_node(N, -1);

    auto calculateDP = [&]() {

        // Reset arrays
        fill(best_cost.begin(), best_cost.end(), INF);
        fill(next_node.begin(), next_node.end(), -1);

        

        int last_stage = S - 1;

        for (int k = 0; k < stage_count[last_stage]; k++) {

            int node = stage_start[last_stage] + k;

            best_cost[node] = 0.0;
            next_node[node] = -1;
        }

       

        for (int st = S - 2; st >= 0; st--) {

            for (int k = 0; k < stage_count[st]; k++) {

                int u = stage_start[st] + k;

                double best = INF;
                int bestv = -1;

                // Examine all outgoing edges
                for (const auto &e : adj[u]) {

                    int v = e.to;

                    // Ignore unreachable destination
                    if (best_cost[v] >= INF / 2)
                        continue;

                    double candidate =
                        e.cur_cost + best_cost[v];

                    if (candidate < best) {

                        best = candidate;
                        bestv = v;
                    }
                }

                best_cost[u] = best;
                next_node[u] = bestv;
            }
        }
    };

 

    calculateDP();


    cout << fixed << setprecision(2);

    cout << "\n______________________________________________\n";
    cout << " Best Costs from Stage-0 Nodes\n";
    cout << "______________________________________________\n";

    for (int k = 0; k < stage_count[0]; k++) {

        int u = stage_start[0] + k;

        if (best_cost[u] >= INF / 2) {

            cout << "Node " << u
                 << ": Unreachable\n";

        } else {

            cout << "Node " << u
                 << ": Cost = "
                 << best_cost[u] << "\n";
        }
    }

    

    auto printPath = [&](int src) {

        if (src < 0 || src >= N) {
            cout << "Error: Invalid source node.\n";
            return;
        }

        // Source must belong to Stage 0
        if (node_stage[src] != 0) {

            cout << "Error: Source node " << src
                 << " is not in Stage 0.\n";

            return;
        }

        if (best_cost[src] >= INF / 2) {

            cout << "No route from node "
                 << src << ".\n";

            return;
        }

        cout << "\nOptimal Path from Node "
             << src << ":\n";

        int cur = src;
        double total = 0.0;

        cout << cur;

        while (next_node[cur] != -1) {

            int nxt = next_node[cur];

            // Find the minimum-cost edge from cur to nxt
            // in case multiple edges exist.
            double edge_cost = INF;

            for (const auto &e : adj[cur]) {

                if (e.to == nxt) {

                    edge_cost = min(edge_cost, e.cur_cost);
                }
            }

            if (edge_cost >= INF / 2) {
                cout << "\nError: Edge not found.\n";
                return;
            }

            total += edge_cost;

            cout << " -> " << nxt;

            cur = nxt;
        }

        cout << "\n\nTotal Route Cost = "
             << total << "\n";
    };



    int src;

    cout << "\nEnter a source node ID from Stage 0 "
         << "to print path (-1 to skip): ";

    cin >> src;

    if (src != -1) {
        printPath(src);
    }

  

    int Q;

    cout << "\nEnter number of live updates "
         << "(0 to finish): ";

    cin >> Q;

    for (int update = 1; update <= Q; update++) {

        int u, v;
        double multiplier;

        cout << "\nUpdate " << update << ":\n";

        cout << "Enter edge update "
             << "(u v multiplier): ";

        cin >> u >> v >> multiplier;

       

        if (u < 0 || u >= N ||
            v < 0 || v >= N) {

            cout << "Invalid node ID. Update skipped.\n";
            continue;
        }

    

        if (multiplier < 0) {

            cout << "Multiplier cannot be negative. "
                 << "Update skipped.\n";

            continue;
        }

        

        bool edge_found = false;

        for (auto &e : adj[u]) {

            if (e.to == v) {

                e.cur_cost =
                    e.base_cost * multiplier;

                edge_found = true;

                cout << "\nEdge "
                     << u << " -> " << v
                     << " updated successfully.\n";

                cout << "Base Cost    = "
                     << e.base_cost << "\n";

                cout << "Multiplier   = "
                     << multiplier << "\n";

                cout << "Current Cost = "
                     << e.cur_cost << "\n";
            }
        }

        
        if (!edge_found) {

            cout << "Error: Edge "
                 << u << " -> " << v
                 << " does not exist.\n";

            continue;
        }


        calculateDP();

      

        cout << "\nAfter Update " << update
             << ", Best Costs:\n";

        for (int k = 0; k < stage_count[0]; k++) {

            int node = stage_start[0] + k;

            if (best_cost[node] >= INF / 2) {

                cout << "Node "
                     << node
                     << ": Unreachable\n";

            } else {

                cout << "Node "
                     << node
                     << ": Cost = "
                     << best_cost[node]
                     << "\n";
            }
        }
    }



    cout << "\n______________________________________________\n";
    cout << " Final Results After All Updates\n";
    cout << "______________________________________________\n";

    for (int k = 0; k < stage_count[0]; k++) {

        int node = stage_start[0] + k;

        if (best_cost[node] >= INF / 2) {

            cout << "Node "
                 << node
                 << ": Unreachable\n";

        } else {

            cout << "Node "
                 << node
                 << ": Minimum Cost = "
                 << best_cost[node]
                 << "\n";
        }
    }


    cout << "\nEnter Stage-0 source node "
         << "to print final optimal path (-1 to exit): ";

    cin >> src;

    if (src != -1) {
        printPath(src);
    }

    return 0;
}