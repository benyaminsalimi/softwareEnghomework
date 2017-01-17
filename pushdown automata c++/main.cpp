#include<iostream>

using namespace std;

struct in_put
{
    char input[100];
    void Enter()
    {
        cin>>input;
    }
};

struct ppm
{
    char move_to;
    char vazn;
    char *pop;
    int pop_count;
    char *push;
    int push_count;
    
public:
    
    ppm()
    {
        pop_count = 0;
        push_count = 0;
    }
    bool operator ==(const ppm &F)
    {
        if(move_to==F.move_to && vazn==F.vazn && pop_count==F.pop_count && push_count==F.push_count)// ppm ==ppm vase in ke raftim ya na
        {
            for(int i=0;i<pop_count;i++)
            {
                if(pop[pop_count]!=F.pop[pop_count])
                    return false;
            }
            for(int i=0;i<push_count;i++)
            {
                if(push[push_count]!=F.push[push_count])
                    return false;
            }
            
            return true;
        }
        else
            return false;
    }
    void operator =(const ppm &F)// =
    {
        move_to=F.move_to;
        vazn=F.vazn;
        pop_count=F.pop_count;
        push_count=F.push_count;
        pop=new char[pop_count];
        for(int i=0;i<pop_count;i++)
            pop[i]=F.pop[i];
        push=new char[push_count];
        for(int i=0;i<push_count;i++)
            push[i]=F.push[i];
    }
    
    
    void add_push(char a)///add kardane yek push be yek ppm kamel kardan sakhtare ppm
    {
        char *temp = new char[push_count];
        for (int i = 0; i < push_count; i++)
            temp[i] = push[i];
        /*delete push;*/
        push_count++;
        push = new char[push_count];
        for (int i = 0; i < push_count - 1; i++)
            push[i] = temp[i];
        delete temp;
        push[push_count - 1] = a;
    }
    
    void add_pop(char a)
    {
        char *temp = new char[pop_count];
        for (int i = 0; i < pop_count; i++)
            temp[i] = pop[i];
        /*delete pop;*/
        pop_count++;
        pop = new char[pop_count];
        for (int i = 0; i < pop_count - 1; i++)
            pop[i] = temp[i];
        delete temp;
        pop[pop_count - 1] = a;
    }
    
};

class level///
{
public:
    char current;
    ppm Move_in;
    ppm bad_ways[100];
    int bad_way_count;
    level()
    {
        bad_way_count=0;
    }
};

class save
{
public:
    char name;//halt
    int count;//moshakhs mikone chandta masir dare
    ppm *ptr;// masir ke mitoone bahahsh harkat kone
    
    bool start;// shoro ! shoro mishe chandta bashe ya na ???!!!
    bool end;// payan
    
    save()//sazande
    {
        count = 0;
        name = '#';
        start = false;
        end = false;
    }
    
    void saving(char input[100])
    {
        int spc_counter = 0;
        ppm *temp = new ppm[count];
        for (int i = 0; i < count; i++)
            temp[i] = ptr[i];
        /*delete ptr;*/
        count++;
        ptr = new ppm[count];
        for (int i = 0; i < count - 1; i++)
            ptr[i] = temp[i];
        delete temp;
        int counter = 2;
        while (true)
        {
            if (counter == 2)
            {
                ptr[count-1].vazn = input[counter];
                counter +=2;
            }
            else if (counter >= 4 && spc_counter == 0)
            {
                if(input[counter]!='@')
                {
                    ptr[count - 1].add_pop(input[counter]);
                }
                if (input[counter + 1] == '|')
                    spc_counter = 1;
                counter +=2;
            }
            else if (spc_counter == 1 && input[counter - 1] == '|')
            {
                ptr[count - 1].move_to = input[counter];
                counter +=2;
            }
            else if (spc_counter == 1 && input[counter - 1] != '|')
            {
                if(input[counter]!='@')
                {
                    ptr[count - 1].add_push(input[counter]);
                }
                if (input[counter + 1] == '\0')
                    break;
                counter +=2;
            }
        }
    }
};


void save_asli(save *asli, in_put *input, int halat_gozar , int halat)///gozar zakhire mikonim !
{
    for (int i = 0; i < halat_gozar; i++)
    {
        int temp=-1;
        int counter = 0;
        for (int j = 0; j < halat; j++)
        {
            if (input[i].input[0] == asli[j].name && asli[j].name != '#')
            {
                asli[j].saving(input[i].input);
                break;
            }
            else if (asli[j].name == '#')
            {
                temp = j;
                counter++;
                break;
            }
        }
        if (counter == 1)
        {
            asli[temp].name = input[i].input[0];
            asli[temp].saving(input[i].input);
        }
    }
    
}


int pooyesh(save *save_asli,char input[100],int halat)
{
    level level_information[100];
    int level = 0;
    level_information[level].current=save_asli[0].name;
    level_information[level].Move_in.move_to='@';
    level_information[level].Move_in.vazn='@';
    char stack[100];
    int stack_rear=0;
    int input_rear=0;
    
    while(true)
    {
        
        int temp=-1;
        int temp2=-1;
        for(int i=0;i<halat;i++)
        {
            if(save_asli[i].name==level_information[level].current)
            {
                temp=i;
                break;
            }
        }
        
        for(int i=0;i<save_asli[temp].count;i++)
        {
            if((save_asli[temp].ptr[i].vazn==input[input_rear] || save_asli[temp].ptr[i].vazn=='@') && input[input_rear]!=NULL)
            {
                if(level_information[level].bad_way_count==0)
                {
                    ///
                    level_information[level].bad_ways[level_information[level].bad_way_count]=save_asli[temp].ptr[i];
                    temp2=i;
                    level_information[level].bad_way_count++;
                    break;
                }
                else
                {
                    for(int j=0;j<level_information[level].bad_way_count;j++)
                    {
                        if(level_information[level].bad_ways[j]==save_asli[temp].ptr[i])
                        {
                            break;
                        }
                        else if(!(level_information[level].bad_ways[j]==save_asli[temp].ptr[i]) && j==level_information[level].bad_way_count-1)
                        {
                            level_information[level].bad_ways[level_information[level].bad_way_count]=save_asli[temp].ptr[i];
                            temp2=i;
                            level_information[level].bad_way_count++;
                            break;
                        }
                    }
                }
                //masir raftim pas biyayim biroon digeh
                if(temp2!=-1)
                    break;
            }
        }
        
        if(temp2==-1 && level==0)
        {
            return 0;
        }
        
        else if(temp2==-1 && level!=0)
        {
            if(level_information[level].Move_in.vazn!='@')
                input_rear--;
            stack_rear=stack_rear-level_information[level].Move_in.push_count;
            for(int i=0;i<level_information[level].Move_in.pop_count;i++)
            {
                stack[stack_rear]=level_information[level].Move_in.pop[i];
                stack_rear++;
            }
            level--;
        }
        
        else if(temp2!=-1)
        {
            int pop_count=0;
            int temp_rear=stack_rear;
            for(int i=0;i<save_asli[temp].ptr[temp2].pop_count;i++)
            {
                if(stack[stack_rear-1]==save_asli[temp].ptr[temp2].pop[i])
                {
                    stack_rear--;
                    pop_count++;
                }
                else
                {
                    stack_rear=temp_rear;
                    break;
                }
            }
            
            if(save_asli[temp].ptr[temp2].pop_count==pop_count)
            {
                for(int i=0;i<save_asli[temp].ptr[temp2].push_count;i++)
                {
                    stack[stack_rear]=save_asli[temp].ptr[temp2].push[i];
                    stack_rear++;
                }
                
                if(save_asli[temp].ptr[temp2].vazn!='@')
                    input_rear++;
                
                level++;
                
                level_information[level].current=save_asli[temp].ptr[temp2].move_to;
                
                level_information[level].Move_in=save_asli[temp].ptr[temp2];
                
            }
        }
        
        
        if(stack_rear==0 && input[input_rear]==NULL)
        {
            for(int i=0;i<halat;i++)
            {
                if(level_information[level].current==save_asli[i].name && save_asli[i].end==true)
                    return 1;
            }
            
            if(level_information[level].Move_in.vazn!='@')
                input_rear--;
            stack_rear=stack_rear-level_information[level].Move_in.push_count;
            for(int i=0;i<level_information[level].Move_in.pop_count;i++)
            {
                stack[stack_rear]=level_information[level].Move_in.pop[i];
                stack_rear++;
            }
            level--;
        }
        else if((stack_rear!=0 && input[input_rear]==NULL) || (stack_rear==0 && input[input_rear]!=NULL))
        {
            return 0;
        }
    }
}
int main()
{
    
    int n_alefba;
    cin>>n_alefba;
    char *alefba=new char[n_alefba];
    for(int i=0;i<n_alefba;i++)
        cin>>alefba[i];
    int halat;
    cin>>halat;
    save *asli=new save[halat];
    int halat_gozar;
    cin>>halat_gozar;
    in_put *input=new in_put[halat_gozar];
    for(int i=0;i<halat_gozar;i++)
        input[i].Enter();
    save_asli(asli,input,halat_gozar,halat);
    int halat_paziresh;
    cin>>halat_paziresh;
    char *paziresh=new char[halat_paziresh];
    for(int i=0;i<halat_paziresh;i++)
        cin>>paziresh[i];
    for(int i=0;i<halat_paziresh;i++)
    {
        for(int j=0;j<halat;j++)
        {
            if(paziresh[i]==asli[j].name)
            {
                asli[j].end=true;
                break;
            }
        }
    }
    int tedad_voroodi;
    cin>>tedad_voroodi;
    in_put *voroodi=new in_put[tedad_voroodi];
    
    for(int i=0;i<tedad_voroodi;i++)
        voroodi[i].Enter();
    
    for(int i=0;i<tedad_voroodi;i++)
    {
        if(pooyesh(asli,voroodi[i].input,halat)==1)
            cout<<"Accept\n";
        else
            cout<<"Not Accept\n";
    }
    
    
}