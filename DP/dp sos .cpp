// O(n * log n)

// sum of subsets
// sos[bit][mask] - сумма по подмаскам mask, которые могут отличаться от mask в первых bit битах

for(int bit = 0; bit < K; ++bit) {
    for(int mask = 0; mask < (1 << K); ++mask) {
        if((mask >> bit) & 1)
            sos[mask] += sos[mask - (1 << bit)];
    }
}

// sum of supersets
// sos[bit][mask] - ...

for(int bit = 0; bit < K; ++bit) {
    for(int mask = 0; mask < (1 << K); ++mask) {
        if((mask >> bit) & 0)
            sos[mask] += sos[mask + (1 << bit)];
    }
}
