//
//  main.cpp
//  Stable Marriage Problem


#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

class stable_marriage_instance
{
    // Private
    int no_of_couples;
    vector <vector <int> > Preference_of_men;
    vector <vector <int> > Preference_of_women;
    vector <int> match_for_men;
    vector <int> match_for_women;
    
    // private member function: checks if anybody is free in boolean "my_array"
    // returns the index of the first-person who is free in "my_array"
    // if no one is free it returns a -1.
    int anybody_free(vector <bool> my_array)
    {
        for (int i = 0; i < no_of_couples; i++)
        {
            if (my_array[i])
            return i;
        }
        return -1;
    }
    
    // private member function: if index1 is ranked higher than index2
    // in a preference array called "my_array" it returns "true"; otherwise
    // it returns "false"
    bool rank_check (vector <int> my_array, int index1, int index2)
    {
        int temp_rank_new = 0;
        int temp_rank_old = 0;
        
        for (int i = 0; i < no_of_couples; i++)
        {
            if (my_array[i] == index1)
            temp_rank_new = i;
            if (my_array[i] == index2)
            temp_rank_old = i;
        }
        
        if (temp_rank_new < temp_rank_old)
        return true;
        else
        return false;
    }
    
    // private member function: implements the Gale-Shapley algorithm
    void Gale_Shapley()
    {
        vector <bool> is_man_free;
        vector <bool> is_woman_free;
        vector <vector <bool> > has_this_man_proposed_to_this_woman;
        
        int man_index = 0, woman_index = 0;
        
        for (int i = 0; i < no_of_couples; i++)
        {
            vector <bool> a;
            has_this_man_proposed_to_this_woman.push_back(a);
        }
        
        // initializing everything
        for (int i = 0; i < no_of_couples; i++)
        {
            is_man_free.push_back(true);
            is_woman_free.push_back(true);
            
            for (int j = 0; j < no_of_couples; j++)
            {
                bool a = false;
                has_this_man_proposed_to_this_woman[i].push_back(a);
            }
            
        }
        
        for (int i = 0; i < no_of_couples; i++)
        {
            match_for_men.push_back(10);
            match_for_women.push_back(10);
        }
        
        // Gale-Shapley Algorithm
        while ((man_index = anybody_free(is_man_free)) >= 0)
        {
            for(int i = 0; i < no_of_couples; i++)
            {
                woman_index = Preference_of_men[man_index][i];
                if (has_this_man_proposed_to_this_woman[man_index][woman_index] == false)
                {
                    has_this_man_proposed_to_this_woman[man_index][woman_index] = true;
                    break;
                }
            }
            
            if(is_woman_free[woman_index])
            {
                is_woman_free[woman_index] = false;
                is_man_free[man_index] = false;
                match_for_men[man_index] = woman_index;
                match_for_women[woman_index] = man_index;
            }
            else
            {
                for(int i = 0;i < no_of_couples; i++)
                {
                    if(match_for_men[i] == woman_index)
                    {
                        match_for_women[woman_index] = i;
                        break;
                    }
                }
                
                if (rank_check(Preference_of_women[woman_index], man_index, match_for_women[woman_index]))
                {
                    is_woman_free[woman_index] = false;
                    is_man_free[man_index] = false;
                    is_man_free[match_for_women[woman_index]] = true;
                    match_for_men[man_index] = woman_index;
                    match_for_women[woman_index] = man_index;
                }
                else
                {
                    is_woman_free[woman_index] = false;
                    is_man_free[man_index] = true;
                }
            }
            if (man_index < no_of_couples)
            man_index++;
            else
            man_index = 0;
        }
    }
    
    
    // private member function: reads data
    void read_data(int argc, const char * argv[])
    {
        ifstream input_filename(argv[1]);
        
        if (input_filename.is_open())
        {
            cout << "Input File Name: " << argv[1] << endl;
            
            input_filename >> no_of_couples;
            cout << endl << "Number of Couples = " << no_of_couples << endl;
            
            cout << endl << "Preferences of Men" << endl;
            
            for (int i = 0; i < no_of_couples; i++)
            {
                vector <int> a;
                Preference_of_men.push_back(a);
            }
            
            for (int i = 0; i <= no_of_couples - 1; i++)
            {
                cout << "(" << i << "): ";
                for (int j = 0; j <= no_of_couples - 1; j++)
                {
                    int a = 0;
                    input_filename >> a;
                    Preference_of_men[i].push_back(a);
                    cout << Preference_of_men[i][j] << " ";
                }
                cout << endl;
            }
            
            for (int i = 0; i < no_of_couples; i++)
            {
                vector<int> a;
                Preference_of_women.push_back(a);
            }
            cout << endl << "Preferences of Women" << endl;
            for (int i = 0; i <= no_of_couples - 1; i++)
            {
                cout << "(" << i << "): ";
                for (int j = 0; j <= no_of_couples - 1; j++)
                {
                    int a = 0;
                    input_filename >> a;
                    Preference_of_women[i].push_back(a);
                    cout << Preference_of_women[i][j] << " ";
                }
                cout << endl;
            }
            
            cout << endl;
        }
        else
        {
            cout << "Input file missing" << endl;
        }
    }
    
    // private member function: print solution
    void print_soln()
    {
        cout << "Matching for Men" << endl;
        for (int i = 0; i < no_of_couples; i++)
        {
            cout << "Man: " << i << " -> " << "Woman: " << match_for_men[i] << endl;
        }
        
        cout << endl << "Matching for Women" << endl;
        for (int i = 0; i < no_of_couples; i++)
        {
            cout << "Woman: " << i << " -> " << "Man: " << match_for_women[i] << endl;
        }
    }
    
    public:
    void solve_it(int argc, const char * argv[])
    {
        read_data(argc, argv);
        
        Gale_Shapley();
        
        print_soln();
        
        exit(0);
        
    }
};

int main(int argc, const char * argv[])
{
    stable_marriage_instance x;
    x.solve_it(argc, argv);
}
