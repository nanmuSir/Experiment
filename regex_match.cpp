#include <iostream>
#include <regex>
using namespace std;

int main() {
    string str = "sigalhu233";

    regex r("[a-z0-9]+");
    cout<<"ÕýÔò±í´ïÊ½£º[a-z0-9]+"<<endl;
    if(regex_match(str,r))
        cout<<"×Ö·û´®£º"<<str<<" Æ¥Åä³É¹¦£¡"<<endl;
    else
        cout<<"×Ö·û´®£º"<<str<<" Æ¥ÅäÊ§°Ü£¡"<<endl;

    cout<<endl<<"ÕýÔò±í´ïÊ½£º\\d+"<<endl;
    if(regex_match(str,regex("\\d+")))
        cout<<"×Ö·û´®£º"<<str<<" Æ¥Åä³É¹¦£¡"<<endl;
    else
        cout<<"×Ö·û´®£º"<<str<<" Æ¥ÅäÊ§°Ü£¡"<<endl;

    cout<<endl<<"ÕýÔò±í´ïÊ½£º\\d+"<<endl;
    if(regex_match(str.begin()+7,str.end(),regex("\\d+")))
        cout<<"×Ö·û´®£º"<<&str[7]<<" Æ¥Åä³É¹¦£¡"<<endl;
    else
        cout<<"×Ö·û´®£º"<<&str[7]<<" Æ¥ÅäÊ§°Ü£¡"<<endl;

    smatch sm;
    cout<<endl<<"ÕýÔò±í´ïÊ½£º([a-z]+)(\\d+)"<<endl;
    if(regex_match(str.cbegin()+5,str.cend(),sm,regex("([a-z]+)(\\d+)"))){
        cout<<"×Ö·û´®£º"<<&str[5]<<" Æ¥Åä³É¹¦£¡"<<endl;
        cout<<"Æ¥Åä×Ö·û´®¸öÊý£º"<<sm.size()<<endl;
        cout<<"·Ö±ðÎª£º";
        for(auto aa:sm)
            cout<<aa.str()<<" ";
        cout<<endl;
    } else
        cout<<"×Ö·û´®£º"<<&str[5]<<" Æ¥ÅäÊ§°Ü£¡"<<endl;

    cmatch cm;
    cout<<endl<<"ÕýÔò±í´ïÊ½£º([a-z]+)(\\d+)"<<endl;
    if(regex_match(str.c_str(),cm,regex("([a-z]+)(\\d+)"))){
        cout<<"×Ö·û´®£º"<<str<<" Æ¥Åä³É¹¦£¡"<<endl;
        cout<<"Æ¥Åä×Ö·û´®¸öÊý£º"<<cm.size()<<endl;
        cout<<"·Ö±ðÎª£º";
        for(auto aa:cm)
            cout<<aa.str()<<" ";
        cout<<endl;
    } else
        cout<<"×Ö·û´®£º"<<str<<" Æ¥ÅäÊ§°Ü£¡"<<endl;
    return 0;
}

