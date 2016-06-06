// Time:  O(m * n * log(m + n) ~ O(m * n * (log(m * n)))
// Space: O(m * n)

// BFS with priority queue (min heap), refactored version.
class Solution {
public:
    /**
     * @param heights: a matrix of integers
     * @return: an integer
     */
    int trapRainWater(vector<vector<int>> &heights) {
        // Init m_, n_, is_visited_.
        m_ = heights.size();
        n_ = heights[0].size();
        is_visited_ = vector<vector<bool>>(m_, vector<bool>(n_, false));

        int trap = 0;

        // Put the cells on the border into min heap.
        for (int i = 0; i < m_; ++i) {
            heap_.emplace(Cell{i, 0, heights[i][0]});
            heap_.emplace(Cell{i, n_ - 1, heights[i][n_ - 1]});
        }
        for (int j = 0; j < n_; ++j) {
            heap_.emplace(Cell{0, j, heights[0][j]});
            heap_.emplace(Cell{m_ - 1, j, heights[m_ - 1][j]});
        }
        const vector<pair<int, int>> directions{{0, -1}, {0, 1},
                                                {-1, 0}, {1, 0}};
        // BFS with priority queue (min heap)
        while (!heap_.empty()) {
            Cell c = heap_.top();
            heap_.pop();
            is_visited_[c.i][c.j] = true;

	        for (const auto& d : directions) {
                trap += fill(heights, c.i + d.first, c.j + d.second, c.height);
	        }
        }

        return trap;
    }

private:
    int fill(const vector<vector<int>>& heights, int i, int j, int height) {
        // Out of border.
        if ( i < 0 || i >= m_ || j < 0 || j >= n_) {
            return 0;
        }

        // Fill unvisited cell.
        if (!is_visited_[i][j]) {
            is_visited_[i][j] = true; // Marked as visited.
            heap_.emplace(Cell{i, j, max(height, heights[i][j])});
            return max(0, height - heights[i][j]); // Fill in the gap.
        }

        return 0;
    }

    struct Cell {
        int i;
        int j;
        int height;
    };

    struct Compare {
        bool operator()(const Cell& a, const Cell& b) {
            return a.height > b.height;
        }
    };

    int m_;
    int n_;
    vector<vector<bool>> is_visited_;
    priority_queue<Cell ,vector<Cell>, Compare> heap_; // Use min heap to get the lowerest cell.
};
