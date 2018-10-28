#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <cmath>

void set_random_seed();
int randn(int n);

struct mm_code_maker{

    void init(int i_length, int i_num){
        length = i_length;
        num = i_num;
    }

    void generate_sequence(){
        for(int i = 0; i < length; i++){
            sequence.push_back(randn(num));
        }
    }

    void give_feedback(const std::vector<int>& attempt, int& black_hits, int& white_hits){
      black_hits = 0;
      white_hits = 0;

      std::vector<std::string> attempt_status, seq_status; //status trackers

      for(int i=0; i<length; i++){
        attempt_status.push_back("N");
        seq_status.push_back("N");
      }

      //find and flag black hits
      for (int i=0; i<length; i++){
        if(attempt[i] == sequence[i]){
          attempt_status[i] = "B";
          seq_status[i] = "B";
          black_hits++;
        }
      }

      //find white hits. Make sure that white hits are not already used by a black/white hit.
      for (int i=0; i<length; i++){
        for (int j=0; j<length; j++){
          if(attempt[i] == sequence[j] && attempt_status[i] == "N" && seq_status[j] == "N"){
            seq_status[j] = "W";
            attempt_status[i] = "W";
            white_hits++;
          }
        }
      }
    }


    std::vector<int> sequence;

    int length;
    int num;
};

struct mm_solver{

    void init(int i_length, int i_num){
        length = i_length;
        num = i_num;
        first_attempt = true;
        attempt_index = 0;
        for(int i=0; i<num; i++){
          possible_attempts.push_back(i);
        }
        rearrange = false;
        insert_new_num = false;
        try_new_arrangement = false;
        hit_record.push_back(0);
        prev_black_hits = 0;
        inserted_index = 0;
        num_to_use = 0;
        times_to_insert = 0;
        successful_swap = false;
    }

    void create_attempt(std::vector<int>& attempt){
      if(!rearrange){
          if (first_attempt){
            for(int i=0; i<length; i++){
                attempt.push_back(0);
            }
          }

          else{
            for(int i=0; i<attempt_index; i++){
              for(int j=0; j<hit_record[i]; j++){
                  attempt.push_back(possible_attempts[i]);
                }
              }
              int difference = length - attempt.size();
              for(int i=0; i<difference; i++){
                attempt.push_back(possible_attempts[attempt_index]);
              }
            }
          }
      else{
        if(insert_new_num){
          bool found_num = false;
          for(int i=0; i<num && !found_num; i++){
            if(hit_record[i] > 0){
              num_to_use = possible_attempts[i];
              times_to_insert = hit_record[i];
              hit_record[i]=0;
              found_num = true;
            }
          }

          for(int j=0; j<times_to_insert; j++){
            bool change_made = false;
            for(int i=0; i<length && !change_made; i++){
              if(ref_vector[i] == num){
                ref_vector[i] = num_to_use;
                change_made = true;
              }
            }

          }
        }
      }


        if(try_new_arrangement){
          bool swapped = false;
          bool found_num_used = false;
          for(int i=0; i<length && !swapped; i++){
            if(!found_num_used && ref_vector[i] == num_to_use){
              found_num_used = true;
              num_used_index = i;
            }
            if(ref_vector[i] == num){
              ref_vector[i] = num_to_use;
              ref_vector[num_used_index] = num;
              num_used_index = i;
              swapped = true;
            }
          }
        }
          for(int i=0; i<length; i++){
            attempt.push_back(ref_vector[i]);
          }
        }


    void learn(std::vector<int>& attempt, int black_hits, int white_hits){
        if(rearrange){
          if(black_hits - prev_black_hits == times_to_insert){
            insert_new_num = true;
            try_new_arrangement = false;
            //some sort of signal that the vector should remain as it is
            //and that you can start looking through hit record again
          }

          else{
            try_new_arrangement = true;
            insert_new_num = false;
          }
          prev_black_hits = black_hits;
        }
        else{
          int total_hits = black_hits + white_hits;
          if(total_hits == length){
            rearrange = true;
            insert_new_num = true;
            for(int i=0; i<length; i++){
              ref_vector.push_back(num);
              //fill a reference vector with dummy values
            }
          }
          if(first_attempt){
            hit_record[0] = total_hits;
            first_attempt = false;
          }
          else{
            int sum=0;
            for(int i=0; i<attempt_index; i++){
              sum+=hit_record[i];
            }
            int new_hits = total_hits - sum;
            hit_record.push_back(new_hits);
          }
          attempt_index++;
      }

}


    void give_feedback2(const std::vector<int>& sequence, const std::vector<int>& attempt, int& black_hits, int& white_hits){
      black_hits = 0;
      white_hits = 0;

      std::vector<std::string> attempt_status, seq_status; //status trackers

      for(int i=0; i<length; i++){
        attempt_status.push_back("N");
        seq_status.push_back("N");
      }

      //find and flag black hits
      for (int i=0; i<length; i++){
        if(attempt[i] == sequence[i]){
          attempt_status[i] = "B";
          seq_status[i] = "B";
          black_hits++;
        }
      }

      //find white hits. Make sure that white hits are not already used by a black/white hit.
      for (int i=0; i<length; i++){
        for (int j=0; j<length; j++){
          if(attempt[i] == sequence[j] && attempt_status[i] == "N" && seq_status[j] == "N"){
            seq_status[j] = "W";
            attempt_status[i] = "W";
            white_hits++;
          }
        }
      }
    }

    int length;
    int num;
    int prev_black_hits;
    int inserted_index;
    int num_to_use;
    int times_to_insert;
    int num_used_index;
    std::vector<int> possible_attempts;
    std::vector<int> hit_record;
    std::vector<int> ref_vector;
    int attempt_index;
    bool first_attempt, rearrange, insert_new_num, try_new_arrangement, successful_swap;

};

/// the main is the same as in the previous example

int main(){


    set_random_seed();

    int length, num, iterations;
    float avg=0;
    std::cout << "enter length of sequence and number of possible values:" << std::endl;
    std::cin >> length >> num;

    //std::cout << "enter number of iterations:" << std::endl;
    //std::cin >> iterations;

//for (int i=0; i<iterations; i++){

    mm_solver solver;
    solver.init(length, num);

    mm_code_maker maker;
    maker.init(length, num);
    maker.generate_sequence();

    int black_hits=0, white_hits=0;
    int attempts_limit = 500000;
    int attempts = 0;
    while((black_hits < length) && (attempts < attempts_limit)){
        std::vector<int> attempt;
        solver.create_attempt(attempt);
        maker.give_feedback(attempt, black_hits, white_hits);
        std::cout << "attempt: " << std::endl;
        for(int i = 0; i < attempt.size(); i++){
            std::cout << attempt[i] << " ";
        }
        std::cout << std::endl;
        std::cout << "black pegs: " << black_hits << " " << " white pegs: " << white_hits << std::endl;
        solver.learn(attempt, black_hits, white_hits);
        attempts++;
    }

    if(black_hits == length){
        std::cout << "the solver has found the sequence in " << attempts << " attempts" << std::endl;
    }
    else{
        std::cout << "after " << attempts << " attempts still no solution" << std::endl;
    }
    std::cout << "the sequence generated by the code maker was:" << std::endl;
    for(int i = 0; i < maker.sequence.size(); i++){
        std::cout << maker.sequence[i] << " ";
    }
    std::cout << std::endl;

  //  avg += attempts;
  //}

  //avg = avg/iterations;

  //std::cout << std::endl << std::endl << "this solution averages " << avg << " attempts" << std::endl;

    return 0;
}

void set_random_seed(){
    std::srand(std::time(0));
}

//generates a random number less than n.
int randn(int n){
    return std::rand() % n;
}
