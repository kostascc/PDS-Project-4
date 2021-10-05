b = 2; % block size

bM = M/b
bN = N/b;
C = zeros([bM bN b b]);

for i=0:(bM-1)
    for j=0:(bN-1)
        C(i+1, j+1, 1:b, 1:b) =     ...
            A((i*b+1):((i+1)*b) , (j*b+1):((j+1)*b));
    end
end
