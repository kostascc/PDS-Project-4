T = zeros(256, 256);

for i=1:256
    for j=1:256
        a = fliplr(de2bi(i-1));
        b = fliplr(de2bi(j-1));
        if(size(a,2) > size(b,2))
            b = [b zeros(1, length(a)-length(b))];
        else
            a = [a zeros(1, length(b)-length(a))];
        end
        t = a' * b;
        %t = t';
        %t = bi2de( t(:).' ) / (i-1);
        %string( num2str( t(:).'  ) )
        %T(i,j) = string( num2str(  t(:).'  ) );
        
        T(i,j) = bi2de( fliplr( t(:).' ) );
        T(i,j) = (T(i,j)) / (i-1);
    end
end
T(1,:) = 0;
%xlswrite('ByteByte.xlsx', T);