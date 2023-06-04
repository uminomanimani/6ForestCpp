g++ -std=c++11 -o main ./src/*.cpp
if [ $? -ne 0 ]; then
    echo "Compilation failed."
else
    $(./main -t 2.5 -b 16)
    if [ $? -eq 0 ]; then
        python ./evaluate.py
    fi
fi
