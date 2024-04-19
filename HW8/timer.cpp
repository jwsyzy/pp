#include "timer.h"
#include <fstream>
#include <iomanip>
#ifdef __MPI
#include <mpi.h>
#endif
using namespace std;
vector<Record> Timer::R;
void Timer::tick(const std::string& class_name,const std::string& function_name)
{
    
    int r_ind=-1;
    for(long unsigned int i=0;i<R.size();i++)
        if (R[i].class_name==class_name && R[i].function_name==function_name)
        {
            r_ind=i;
            break;
        }   
    if (r_ind==-1)
    {
        R.push_back(Record(class_name,function_name));
 	r_ind=R.size()-1;
    }
    int i=r_ind;    
    if (R[i].running_flag==false)
    {
    R[i].calls++;
    R[i].running_flag=true;
#ifdef __MPI
    R[i].start_time=MPI_Wtime();
#else
    R[i].start_time=clock();
#endif
    }
    else{
    R[i].running_flag=false;

#ifdef __MPI
    R[i].end_time=MPI_Wtime();
#else
    R[i].end_time=clock();
#endif
    R[i].total_time+=R[i].end_time-R[i].start_time;
    }
}

void Timer::print_record()
{   
    cout<<setw(15)<<"-----ClassName"
	    <<setw(15)<<"--FunctionName"
        <<setw(10)<<"----Time(1e-6Sec)"
	    <<setw(10)<<"----Calls"
	    <<setw(20)<<"-----AvgTimePerCall"
	    <<setw(10)<<"-------Per"<<endl;
    double sum_total_time=0;
    for(long unsigned int i=0;i<R.size();i++)
    {
        sum_total_time+=R[i].total_time;
    }
    cout<<fixed<<setprecision(4);
    for(long unsigned int i=0;i<R.size();i++)
    {
        cout<<setw(15)<<R[i].class_name
		<<setw(15)<<R[i].function_name
        <<setw(15)<<R[i].total_time
		<<setw(10)<<R[i].calls
        <<setw(20)<<R[i].total_time/R[i].calls
		<<setw(10)<<(R[i].total_time/sum_total_time)*100<<"%"
		<<endl;
    }
}



void Timer::save_record(std::ofstream& output_file) {
    output_file << std::setw(15) << "-----ClassName"
                << std::setw(15) << "--FunctionName"
                << std::setw(10) << "----Time(Sec)"
                << std::setw(10) << "----Calls"
                << std::setw(20) << "-----AvgTimePerCall"
                << std::setw(10) << "-------Per" << std::endl;

    double sum_total_time = 0;
    for (size_t i = 0; i < R.size(); ++i) {
        sum_total_time += R[i].total_time;
    }

    output_file << std::fixed << std::setprecision(4);
    for (size_t i = 0; i < R.size(); ++i) {
        output_file << std::setw(15) << R[i].class_name
                    << std::setw(15) << R[i].function_name
                    << std::setw(15) << R[i].total_time
                    << std::setw(10) << R[i].calls
                    << std::setw(20) << R[i].total_time / R[i].calls
                    << std::setw(10) << (R[i].total_time / sum_total_time) * 100 << "%" << std::endl;
    }
}


void Timer::clear_record()
{
    R.clear();
}