function a = e_greedy(s,p,epsilon)
%function a = e_greedy(s,p,epsilon)

if rand() < epsilon
    a = randi(4);
else
    a = p(s+1);
end
    
    
   