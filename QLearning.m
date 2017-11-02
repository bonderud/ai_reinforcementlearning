function Q = QLearning ( Q, n, epsilon, alpha )
%function Q = QLearning ( Q, n, eplison, alpha )

p = getPolicy(Q);

for i = 1:n
    s = 0;
    while ~isGoal(s)
        a = e_greedy(s,p,epsilon);
        [snew,r] = nextState(s,a);
        astar = p(snew+1);
        tdError = Q(snew+1,astar) + r - Q(s+1,a);
        Q(s+1,a) = Q(s+1,a) + alpha * tdError;
        s = snew;
        p = getPolicy(Q);
    end
end

        
