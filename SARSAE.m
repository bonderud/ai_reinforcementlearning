function Q = SARSAE ( Q, n, epsilon, alpha, lambda )
%function Q = SARSAE ( Q, n, eplison, alpha, lambda )

p = getPolicy(Q);

for i = 1:n
    s = 0;
    a = e_greedy(s,p,epsilon);
    elig = Q .* 0;
    elig(s+1,a) = 1;
    while ~isGoal(s)
        [snew,r] = nextState(s,a);
        anew = e_greedy(snew,p,epsilon);
        tdError = Q(snew+1,anew) + r - Q(s+1,a);
        %Q(s+1,a) = Q(s+1,a) + alpha * tdError;
        Q = Q + elig .* (alpha * tdError);
        elig = elig .* lambda;
        s = snew;
        a = anew;
        elig(s+1,a) = 1;
        p = getPolicy(Q);
    end
end

        
