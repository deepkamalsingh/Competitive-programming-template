// Multiplies many polynomials whose total degree is n in O(n log^2 n).
    template<typename T>
    vector<T> mod_multiply_all(const vector<vector<T>> &polynomials) {
        if (polynomials.empty())
            return {1};
 
        struct compare_size {
            bool operator()(const vector<T> &x, const vector<T> &y) {
                return x.size() > y.size();
            }
        };
 
        priority_queue<vector<T>, vector<vector<T>>, compare_size> pq(polynomials.begin(), polynomials.end());
 
        while (pq.size() > 1) {
            vector<T> a = pq.top(); pq.pop();
            vector<T> b = pq.top(); pq.pop();
            pq.push(mod_multiply(a, b));
        }
 
        return pq.top();
    }