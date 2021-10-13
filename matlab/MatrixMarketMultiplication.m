
filename = '../resources/1138_bus.mtx';

[rows, cols, entries, rep, field, symm] = mminfo(filename);

[A, rows, cols, entries] = mmread(filename);

A = full(A);
A = (A~=0);

% for i=1:size(A,2)
%     if (A(i,i) ~= 0)
%         entries = entries-1;
%     end
%     A(i,i) = 0;
% end

flipped = 0;

for i=1:size(A,2)
    for j=i+1:size(A,2)
        
        if(A(i,j)>0)
            flipped = flipped + 1;
            A(i,j) = 0;
            %A(j,i) = 1;
        end
        
        
    end
end

entries = nnz(A);

flipped

AAnnz = nnz((A* A)>0)

ATAnnz = nnz((A' * A)>0)

AATnnz = nnz((A * A')>0)

ATATnnz = nnz((A' * A')>0)

AAAnnz = nnz((A.*(A* A))>0)

AATAnnz = nnz((A.*(A' * A))>0)

AAATnnz = nnz((A.*(A * A'))>0)

ATAAnnz = nnz((A.*(A* A))>0)