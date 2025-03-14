// sum of subsets
// sos[bit][mask] - сумма по подмаскам mask, которые могут отличаться от mask в первых bit битах
// O(n * log n)
for(int bit = 0; bit < K; ++bit) {
    for(int mask = 0; mask < (1 << K); ++mask) {
        if((mask >> bit) & 1)
            sos[mask] += sos[mask - (1 << bit)];
    }
}
