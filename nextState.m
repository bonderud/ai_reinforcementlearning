function [snew,r] = nextState ( s, a )
%function [snew,r] = nextState ( s, a )

row = floor(s/8);
col = mod(s,8);

r = -1;
if a == 1
    if row < 3
        row = row + 1;
    end
elseif a == 2
    if row == 0 && col == 0
        row = 0;
        col = 0;
        r = -100;
    elseif col < 7
        col = col + 1;
    end
elseif a == 3
    if row > 1
        row = row - 1;
    elseif row == 1
        if col >=2 && col <= 6 
            row = 0;
            col = 0;
            r = -100;
        else
            row = row - 1;
        end
    end
elseif a == 4
    if col > 0
        col = col - 1;
    end
end

snew = row*8 + col;
