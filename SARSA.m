function Q = SARSA ( Q, n, epsilon, alpha )
%function Q = SARSA ( Q, n, eplison, alpha )

p = getPolicy(Q);

for i = 1:n
    s = 0;
    a = e_greedy(s,p,epsilon);
    while ~isGoal(s)
        [snew,r] = nextState(s,a);
        anew = e_greedy(snew,p,epsilon);
        tdError = Q(snew+1,anew) + r - Q(s+1,a);
        Q(s+1,a) = Q(s+1,a) + alpha * tdError;
        s = snew;
        a = anew;
        p = getPolicy(Q);
    end
end

        
