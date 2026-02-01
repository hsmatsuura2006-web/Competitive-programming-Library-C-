//条件を満たす最小値//	
ll ok = n, ng = -1;
while (ng + 1 < ok) {
    ll med = (ok + ng) / 2;
    if (a[med] >= b[i]) {
        ok = med;
    } else {
        ng = med;
    }
}

//条件を満たす最大値//
ll ok = -1, ng = n; 
while (ok + 1 < ng) {
    ll med = (ok + ng) / 2;
    if (a[med] <= b[i]) { 
        ok = med; 
    } else {
        ng = med; 
    }
}
