#include <mpi.h>
#include <iostream>
#include <string>

int main(int argc, char** argv) {
    // 初始化 MPI
    MPI_Init(&argc, &argv);

    int rank, size;
    // 获取当前进程的排名和总进程数
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // 如果只有一个进程，就没必要发送消息
    if (size == 1) {
        std::cout << "只有一个进程，不需要通信" << std::endl;
        MPI_Finalize();
        return 0;
    }

    if (rank == 0) {
        // 如果是进程 0，发送消息给其他进程
        std::string message = "Hello, World!";
        for (int i = 1; i < size; ++i) {
            MPI_Send(message.c_str(), message.size() + 1, MPI_CHAR, i, 0, MPI_COMM_WORLD);
        }
    } else {
        // 如果不是进程 0，接收来自进程 0 的消息
        char buffer[100];
        MPI_Recv(buffer, 100, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        std::cout << "进程 " << rank << " 收到消息: " << buffer << std::endl;
    }

    // 结束 MPI
    MPI_Finalize();
    return 0;
}
