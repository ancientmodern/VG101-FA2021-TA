filelist = ls;
% fid = fopen('Auto_result.csv', 'w');
% fprintf(fid, 'name,P1,P2,P3,P4,P5\n');
for i = 1:length(filelist)
    dir = filelist(i, :);
    if contains(dir, 'mid')
        cd(dir);
        disp(dir);
        fprintf(fid, '%s,%d,%d,%d,,%d\n', dir, testP1, testP2, testP3, testP5);
        testP1;
        testP2;
        testP3;
        testP5;
        cd ..;
    end
end
% fclose(fid);

function ret = baseP1(N)
    arr = 1:1:N;
    ret = arr .^ 2;
end

function point = testP1
    in = [1 5 10 20 100];
    point = 0;
    for i = 1:5
        try
            ret = Problem1(in(i));
            correct = baseP1(in(i));
            point = point + 4 * isequal(ret, correct);
        catch
        end
    end
end

function ret = baseP2(N)
    arr = 0:1:N;
    ret = sqrt(8 * sum(1 ./ (2 .* arr + 1).^2));
end

function point = testP2
    in = [0 1 100 1000 10000];
    point = 0;
    for i = 1:5
        try
            ret = Problem2(in(i));
            correct = baseP2(in(i));
            point = point + 4 * (ret <= correct + 0.0001 && ret >= correct - 0.0001);
        catch
        end
    end
end

function [varName, varValue] = baseP3(str)
    str = strrep(str, ' ', '');
    arr = split(str, '=');
    varName = char(arr(1));
    varValue = str2double(arr(2));
end

function point = testP3
    in = {'a=1', 'b =2', 'c= 3', 'd = 123', 'adfegdsg =    -1.5', 'bug = -2.543', 'thisisarealrealreallongname    = -2223.1', 'git              =                 -5.444', 'love =     5.677', 'a    =  520021911399'};
    point = 0;
    for i = 1:length(in)
        try
            [n, v] = Problem3(char(in(i)));
            [cn, cv] = baseP3(char(in(i)));
            point = point + 1 * isequal(n, cn) + 1 * isequal(v, cv);
        catch
        end
    end
end

function [number, appearance] = baseP5(arr) 
    number = unique(sort(arr));
    appearance = zeros(1, length(number));
    for i = 1:length(number)
        appearance(i) = length(find(arr == number(i)));
    end
end

function point = testP5
    in = {[0];[5 5 5 5 5];[1 3 1 4 0 7 7 8];[1 2 3 4 5];[6 5 4 3];[1 8 3 0 7 2 7 0 7 2 2 4 9 8 7 2 0 2];[1 1 1];[1 2 7 3 2 9 0 2 1 2 3 9 2 2 3 2 9 7 8];[1 2 9 8 2 4 7 1 9 8 2 3 4 8 2 4 3 0 9 1 2 7 2 4 2 8 7 2 9 2 9 2 8 9 3 2 0 2 0 3 0 2 0 1 2 2 9 8 7 0 8 0 8 0 8 0 6 9 6];[9 9 9]};
    % in = {[0];[5 5 5]};
    point = 0;
    for i = 1:2
        try
            [n, a] = Problem5(cell2mat(in(i)));
            [cn, ca] = baseP5(cell2mat(in(i)));
            point = point + 1 * isequal(n, cn) + 1 * isequal(a, ca);
        catch
        end
    end
end