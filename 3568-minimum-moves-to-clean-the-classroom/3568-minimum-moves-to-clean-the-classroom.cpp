class Solution {
public:
    struct State {
        int r, c;
        int mask;
        int energy;
    };

    int minMoves(vector<string>& classroom, int energy) {
        int m = classroom.size();
        int n = classroom[0].size();

        int sr = 0, sc = 0;
        int litterCount = 0;

        // Assign each litter an ID: 0, 1, 2, ...
        vector<vector<int>> litterId(m, vector<int>(n, -1));

        for (int r = 0; r < m; r++) {
            for (int c = 0; c < n; c++) {
                if (classroom[r][c] == 'S') {
                    sr = r;
                    sc = c;
                } 
                else if (classroom[r][c] == 'L') {
                    litterId[r][c] = litterCount++;
                }
            }
        }

        int allMask = (1 << litterCount) - 1;

        if (allMask == 0)
            return 0;

        /*
            best[r][c][mask] = maximum remaining energy
            with which we have reached (r, c)
            after collecting "mask".
        */
        vector<vector<vector<int>>> best(
            m,
            vector<vector<int>>(n, vector<int>(1 << litterCount, -1))
        );

        queue<State> q;

        best[sr][sc][0] = energy;
        q.push({sr, sc, 0, energy});

        int dr[] = {1, -1, 0, 0};
        int dc[] = {0, 0, 1, -1};

        int moves = 0;

        while (!q.empty()) {
            int sz = q.size();

            while (sz--) {
                auto [r, c, mask, currEnergy] = q.front();
                q.pop();

                // All litter collected.
                if (mask == allMask)
                    return moves;

                // Cannot make another move unless on R.
                if (currEnergy == 0)
                    continue;

                for (int d = 0; d < 4; d++) {
                    int nr = r + dr[d];
                    int nc = c + dc[d];

                    // Outside grid.
                    if (nr < 0 || nr >= m || nc < 0 || nc >= n)
                        continue;

                    // Obstacle.
                    if (classroom[nr][nc] == 'X')
                        continue;

                    int newEnergy = currEnergy - 1;
                    int newMask = mask;

                    // Collect litter.
                    if (classroom[nr][nc] == 'L') {
                        int id = litterId[nr][nc];
                        newMask |= (1 << id);
                    }

                    // Reset energy.
                    if (classroom[nr][nc] == 'R') {
                        newEnergy = energy;
                    }

                    /*
                        If we have already reached this exact
                        (nr, nc, newMask) with >= energy,
                        this state is useless.
                    */
                    if (newEnergy <= best[nr][nc][newMask])
                        continue;

                    best[nr][nc][newMask] = newEnergy;

                    q.push({
                        nr,
                        nc,
                        newMask,
                        newEnergy
                    });
                }
            }

            moves++;
        }

        return -1;
    }
};