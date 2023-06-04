if ! test -d "./build"; then
    mkdir "./build"
fi

( 
    cd ./build
    cmake ..
    if [ $? -ne 0 ]; then
        echo "Compilation failed."
    else
        cmake --build .
    fi
)

$(./main -t 2.5 -b 16)
if [ $? -eq 0 ]; then
    python ./evaluate.py
fi