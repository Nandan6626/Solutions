
class Solution {
public:
    int shortestPath(int n, vector<vector<int>>& edges, string labels, int k) {

        vector<vector<pair<int,int>>> adj(n);

        for (auto &e : edges) {
            adj[e[0]].push_back({e[1], e[2]});
        }

        // State: node * (k+1) + consecutive count
        // Previous character is determined by labels[node].
        const long long INF = LLONG_MAX / 4;

        vector<vector<long long>> dist(n, vector<long long>(k + 1, INF));

        using P = tuple<long long, int, int>;

        priority_queue<P, vector<P>, greater<P>> pq;

        dist[0][1] = 0;
        pq.push({0, 0, 1});

        while (!pq.empty()) {

            auto [d, u, cnt] = pq.top();
            pq.pop();

            if (d != dist[u][cnt]) continue;

            if (u == n - 1) return (int)d;

            for (auto [v, w] : adj[u]) {

                int newCnt = (labels[u] == labels[v]) ? cnt + 1 : 1;

                if (newCnt > k) continue;

                long long nd = d + w;

                if (nd < dist[v][newCnt]) {
                    dist[v][newCnt] = nd;
                    pq.push({nd, v, newCnt});
                }
            }
        }

        return -1;
    }
};
