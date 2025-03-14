// sum of subsets
// O(n * log n)
for(int bit = 0; bit < K; ++bit) {
    for(int mask = 0; mask < (1 << K); ++mask) {
        if((mask >> bit) & 1)
            sos[mask] += sos[mask - (1 << bit)];
    }
}
