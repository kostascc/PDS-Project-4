clc; 

columns = 5;
length = 2;
height = 8;
blocks = columns * height/length;
csci = [1 2 4 7 8 4 7 1 6];
cscp = [1 6 6 7 8 10 ];
cscb = [];

% For each column
for j = 1 : columns
    b = 1;
    cscb = [cscb cscp(j)];

    % For each row in the column
    for i = cscp(j) : (cscp(j+1)-1)

       c = csci(i);
       
       % Fill previous blocks
       while( c > (b)*length )
           cscb = [cscb i];
           b = b+1;
       end

    end 
    
    % Fill the rest of the blocks
    %i = cscb(size(cscb, 2));
    i = (cscp(j+1));
    cscb = [cscb repmat([i], [1 (height/length-b)])];
        
end

% Add end of table index
cscb = [cscb i+1];

% Print
cscb'