%fmt = format("long");
%format(fmt)
digits(128)

T = zeros(256, 256);

for i=1:256
    for j=1:256
        
        a = de2bi(i-1);
        b = de2bi(j-1);
        
        a = [a zeros(1, 8-length(a))];
        b = [b zeros(1, 8-length(b))];
        
        a = fliplr(a);
        b = fliplr(b);
        
        t = a' * b;
        t = t';
        %F(i,j) = t;
        
        
        t = [t(1,:) t(2,:) t(3,:) t(4,:) t(5,:) t(6,:) t(7,:) t(8,:)];
        
        H(i,j) = string(binaryVectorToHex(t)); 
        
        F(i,j) = string(num2str(t));
        
        bi2de( fliplr( t )  );
        T(i,j) = int64(bi2de( fliplr( t )  ));
        %T(i,j) = (T(i,j));
        
        test = (i-1) * LU(j);
        
        %if (int64(T(i,j)) ~= int64(test))
        %   disp('Test Error at');
        %   i, j
        %   test
        %   return;
        %end
        
        
    end
end
T(1,:) = 0;

if(nnz(T(mod(T,1)>0)))
   disp 'Decimals found!'; 
end

%xlswrite('ByteByte.xlsx', T);

% strrep( T{i, j}, ' ', '' )

fid = fopen( 'hex.csv', 'w' );
for i = 1 : 256
    for j = 1 : 256
        fprintf( fid, '"%s",', H(i,j));
    end
    fprintf( fid, '\n');
end
fclose( fid );