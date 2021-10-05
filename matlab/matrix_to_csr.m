% A, M, N required

idx = [];
ptr = [];
nz = 0;

for j=1:M
    ptr = [ptr nz+1];
    for i=1:N
        if (A(i,j) > 0)
            nz = nz+1;
            idx(nz) = i;
        end
    end
end