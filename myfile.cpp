//20218004 Rana Mohamed Hamza
//20216077 Fatma Essam Elden
//20216009 Ahmed Adel Mohammed
//20216008 Ahmed Tarek Ahmed
//20216075 Fady Micheal Mofid
#include <iostream>
#include <stack>
using namespace std;
struct Call
{
    int n;         //parameters
    int a, b;       //local variables
    int cur_loc;   //location of the next statement to be executed
};
int G(int n)       //Non-recursive version of F()
{
    Call initial_call;
    initial_call.n = n;
    initial_call.cur_loc = 0;

    stack<Call> st;
    st.push(initial_call);
    int last_ret_val = 0;    //Return value of last finished call
    while (!st.empty())
    {
        Call& call = st.top();
        if(call.cur_loc == 0)
        {
            if (call.n <= 1) 
            {
                //Call finished, save return value and pop stack
                last_ret_val = 1;
                st.pop();
            }
            else
            {
                //Make new child call F(n-1) and push to stack
                Call new_call;
                new_call.cur_loc = 0;
                new_call.n = call.n - 1;
                st.push(new_call);

                //Update current location inside parent call
                call.cur_loc = 1;
            }
        }
        else if (call.cur_loc == 1)
        {
            //Do required computations
            call.a = call.n * last_ret_val;

            //Make new child call F(n/2) and push to stack
            Call new_call;
            new_call.cur_loc = 0;
            new_call.n = call.n / 2;
            st.push(new_call);

            //Update current location inside parent call
            call.cur_loc = 2;
        }
        else if (call.cur_loc == 2) 
        {
            //Do required computations
            call.a = call.a + 7 * last_ret_val;

            //Make new child call F(n-3-a%2) and push to stack
            Call new_call;
            new_call.cur_loc = 0;
            new_call.n = call.n - 3 - call.a % 2;
            st.push(new_call);

            //Update current location inside parent call
            call.cur_loc = 3;
        }
        else if (call.cur_loc == 3) {
            //Do required computations
            call.b = last_ret_val;

            //Call finished, save return value and pop satck
            last_ret_val = call.a + call.b;
            st.pop();
        }
    }
    return last_ret_val;

}
int F(int n) {
    if (n <= 1)
        return 1;
    int a = n * F(n - 1) + 7 * F(n / 2);
    int b = F(n - 3 - a % 2);
    return a + b;
}
int main() {
    //Test cases
    for (int i = 1; i <= 20; ++i) 
    {
        cout << "F(" << i << "):" << F(i) << " vs the non recursive function G(" << i << "): " << G(i) << endl;
    }
    return 0;
}