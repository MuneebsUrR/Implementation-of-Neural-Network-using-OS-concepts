/*OS PROJECT
MUNEEB UR REHMAN
SOHAIL SHAHBAZ
*/
#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <sys/wait.h>
#include <string>
#include <thread>
#include <iomanip>
#include <sstream>
#include "stack.h"
#include "data.h"
using namespace std;

const int noOfLayers = 5;

sem_t lock;
Stack<double> st; // stack for tracking values

double finalOutput = 0.0; // variable to store the final result

double valuesArr[2]; // array of x1 and x2 (formulas)

struct Neuron
{
    int NeuronNum;
    int weights;
};

void critical_Section(int id)
{

    int fd = open("my_pipe", O_RDONLY); // creating pipe for reading and writing
    sem_wait(&lock);
    for (int i = 0; i < 1; i++) // rows of answer array [1][8 ]
    {
        read(fd, layersAns[i], sizeof(layersAns[i]));
    }
    close(fd);

    double val = 0.0;
    double dummy[1][8];
    for (int i = 0; i < 8; i++) // layer rows
    {
        for (int k = 0; k < 8; k++) // ans values
        {
            for (int j = 0; j < 8; j++) // layer col
            {
                val += layersAns[0][k] * layerWeights[id][i][j];
            }
        }
        dummy[0][i] = val;
        val = 0;
    }
    for (int i = 0; i < 8; i++)
    {
        layersAns[0][i] = dummy[0][i];
        st.push(layersAns[0][i]);
    }

    fd = open("my_pipe", O_WRONLY);
    for (int i = 0; i < 1; i++)
    {
        write(fd, layersAns[i], sizeof(layersAns[i]));
    }
    close(fd);
    sem_post(&lock);
}

struct network_Layers
{
    int num_layers; // total number of layers

    network_Layers(int num)
    {

        num_layers = num; // total numbers layers

        // Writing initial answer of input layers on pipe
        int fd = open("my_pipe", O_WRONLY); // for writing only

        for (int k = 0; k < 2; k++)
        { // input layer neurons

            for (int j = 0; j < 8; j++)
            { // 8 values of neurons

                for (int i = 0; i < 2; i++)
                {                                                                   // 2 values of input
                    layersAns[0][j] += inputvalues[i] * inputLayerWeights[k][0][j]; // generating input layers
                }
            }
        }

        for (int i = 0; i < 8; i++)
        { // inserting values of input layer in stack
            st.push(layersAns[0][i]);
        }

        for (int i = 0; i < 1; i++)
        {
            write(fd, layersAns[i], sizeof(layersAns[i]));
        }
        // close named pipe
        // num_layers--;
        close(fd);
    }
    double formula1(double x)
    {

        double value = ((x * x) + x + 1) / 2;
        stringstream ss;
        ss << value;
        std::string str = ss.str();
        std::string significand = str.substr(0, str.find('e'));
        double result = std::stod(significand);
        return result;
    }
    double formula2(double x)
    {
        double value = ((x * x) - x) / 2;
        stringstream ss;
        ss << value;
        std::string str = ss.str();
        std::string significand = str.substr(0, str.find('e'));
        double result = std::stod(significand);
        return result;
    }

    void forwardPropagation()
    {
        cout << "Forward Propagation start processing\n";
        sleep(2);
        pid_t pid;
        thread processes[num_layers];
        // Start child processes in a loop
        for (int i = 0; i < num_layers; i++)
        {
            processes[i] = thread(critical_Section, i);
        }
        // Wait for all child processes to complete
        for (int i = 0; i < num_layers; i++)
        {
            processes[i].join();
        }

        // output layer multiplying
        for (int j = 0; j < 8; j++)
            for (int i = 0; i < 8; i++)
            {
                layersAns[0][j] += layersAns[0][i] * outputLayer[0][j];
            }
        for (int i = 0; i < 8; i++)
            st.push(layersAns[0][i]);
    }

    void backPropagationCriticalSection()
    {

        sem_wait(&lock);
        int counter = 0; // counter to get values from stack according to size of layer array like here is 8 rows in the layer array

        while (counter != 8 && !st.isEmpty())
        {
            cout << st.peek() << " ";
            st.pop();
            counter++;
        }
        cout << endl;

        counter = 0;
        int fd = open("values", O_RDONLY); // creating pipe for reading and writing
        read(fd, valuesArr, sizeof(valuesArr));
        close(fd);
        valuesArr[0] = formula1(valuesArr[0]);
        valuesArr[1] = formula2(valuesArr[1]);
        cout << "The value of x1 = " << valuesArr[0] << endl;
        cout << "The value of x2 = " << valuesArr[1] << endl;
        int fd2 = open("values", O_WRONLY);
        write(fd2, valuesArr, sizeof(valuesArr));
        close(fd2);
        sem_post(&lock);
    }

    void backPropagation()
    {

        for (int i = 0; i < 8; i++)
        { // size of answer array [1][8]
            finalOutput += layersAns[0][i];
        }
        cout << "\nFinal ouput I get in End after forward propagation :\n";

        cout << finalOutput << endl;
        cout << "--------------------------" << endl;
        cout << "Back Propagation start processing\n";
        sleep(2);

        // writing values in pipe
        valuesArr[0] = formula1(finalOutput);
        valuesArr[1] = formula2(finalOutput);
        int fd = open("values", O_WRONLY);
        write(fd, valuesArr, sizeof(valuesArr));
        cout << "The value of x1 on output = " << valuesArr[0] << endl;
        cout << "The value of x2 on output = " << valuesArr[1] << endl;
        close(fd);
        int totalLayers = num_layers + 1 + 1; // input layer + remaining layers + output layer

        for (int i = totalLayers; i > 0; i--)
        {
            cout << "----Process " << i << " Layer values----" << endl;
            backPropagationCriticalSection();
        }
        // last values after multiplying with input values
        fd = open("values", O_RDONLY); // creating pipe for reading and writing
        read(fd, valuesArr, sizeof(valuesArr));
        close(fd);
        valuesArr[0] = formula1(valuesArr[0]);
        valuesArr[1] = formula2(valuesArr[1]);
        cout << "\nThe value of x1 on input = " << valuesArr[0] << endl;
        cout << "The value of x2 on input = " << valuesArr[1] << endl;
        inputvalues[0] = valuesArr[0];
        inputvalues[1] = valuesArr[1];
    }

    void printOutput()
    {
        st.display();
    }
    void startProcessing()
    {
        sem_t processLock;
        sem_init(&processLock, 0, 1);
        for (int i = 0; i < 1; i++)
        {
            pid_t id = fork(); // Multiprocessing
            sem_wait(&processLock);
            if (id < 0)
            {
                cerr << "Error in creating process";
                exit(1);
            }
            else if (id == 0)
            {

                forwardPropagation();
                backPropagation();
            }
            else if (id == 1)
            {

                wait(NULL);
            }
            sem_post(&processLock);
        }
    }
};

int main()
{

    sem_init(&lock, 0, 1);
    network_Layers obj(noOfLayers); // No of layers
    obj.startProcessing();
}
