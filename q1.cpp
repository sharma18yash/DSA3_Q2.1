#include<strings.h>
#include<stdlib.h>
#include<iostream>
#include<vector>
using namespace std;
vector<string> autoComp;
vector<string> autoCorr;
struct trieNode
{
    struct trieNode* child[26];
    bool wordEnd;
};
struct trieNode *nodeInit()
{
    struct trieNode *pNode = new trieNode;
    pNode->wordEnd=false;
    for(int i=0; i<26; i++)
        pNode->child[i] = NULL;

    return pNode;
}
void insert(struct trieNode *root, string word)
{
    struct trieNode *temp = root;
    for(int i=0; i<word.length(); i++)
    {
        int index = word[i] - 'a';
        // cout<<index<<" ";
        if(!temp->child[index])
            temp->child[index] = nodeInit();
        
        temp = temp->child[index];
    }
    temp->wordEnd=true;
}
bool spellCheck(struct trieNode* root, string word)
{
    struct trieNode *temp = root;
    for(int i=0; i<word.size(); i++)
    {
        int index = word[i] - 'a';
        if(!temp->child[index])
            return false;
        temp = temp->child[index];
    }
    return temp->wordEnd;
}
bool isLeafNode(struct trieNode* root)
{
    return root->wordEnd != false;
}
bool isLastNode(struct trieNode* root)
{
    for (int i = 0; i < 26; i++)
        if (root->child[i])
            return 0;
    return 1;
}
void display(struct trieNode* root, char str[], int level)
{
    if(isLeafNode(root))
    {
        str[level] = '\0';
        cout<<str<<endl;
    }
    int i;
    for(int i=0; i<26; i++)
    {
        if(root->child[i])
        {
            str[level] = i+'a';
            display(root->child[i], str, level+1);
        }
    }
}
void helper(struct trieNode* root, string prefix)
{
    if(root->wordEnd)
    {
        autoComp.push_back(prefix);
        // cout<<prefix<<endl;
    }
    if(isLastNode(root))
        return;
    for(int i=0; i<26; i++)
    {
        if(root->child[i])
        {
            prefix.push_back(97+i);
            helper(root->child[i], prefix);
            prefix.pop_back();
        }
    }
}
int autoComplete(struct trieNode* root, string word)
{
    struct trieNode* temp = root;
    for(int i=0; i<word.length(); i++)
    {
        int index = word[i] - 'a';
        if(!temp->child[index])
            return 0;
        temp = temp->child[index];
    }
    bool isWord = (temp->wordEnd==true);
    bool isLast = isLeafNode(temp);
    if(isWord && isLast)
    {
        // cout<<word<<endl;
        autoComp.push_back(word);
        return -1;
    }
    if(!isLast)
    {
        string prefix = word;
        helper(temp, prefix);
        return 1;
    }
    return 1;
}
int levenstienDist(string word1, string word2)
{
    int m  = word1.size();
    int n = word2.size();
    int dp[m+1][n+1];
    for(int i=0; i<=m; i++)
    {
        for(int j=0; j<=n; j++)
        {
            if(i==0)
                dp[i][j]=j;
            else if(j==0)
                dp[i][j]=i;
            else if(word1[i-1]==word2[j-1])
                dp[i][j] = dp[i-1][j-1];
            else
                dp[i][j] = 1+min(min(dp[i-1][j], dp[i][j-1]), dp[i-1][j-1]);
        }
    }
    return dp[m][n];
}
void autoCorrect(struct trieNode* root, string word, char str[], int level)
{
    if(isLeafNode(root))
    {
        str[level] = '\0';
        // cout<<str<<endl;
        int n = levenstienDist(word, str);
        // cout<<n<<" ";
        if(n<=3)
        {
            autoCorr.push_back(str);
            // cout<<str<<endl;
        }
    }
    int i;
    for(int i=0; i<26; i++)
    {
        if(root->child[i])
        {
            str[level] = i+'a';
            autoCorrect(root->child[i], word, str, level+1);
        }
    }
}
int main()
{
    int n;
    cin>>n;
    struct trieNode *root = nodeInit();
    for(int i=0; i<n; i++)
    {
        string word;
        cin>>word;
        insert(root, word);
    }
    // int level=0;
    // char str[100];
    // display(root, str, level);
    int ch;
    cin>>ch;
    if(ch==1)
    {
        string word;
        cin>>word;
        if(spellCheck(root, word))
            cout<<1;
        else
            cout<<0;
    }
    if(ch==2)
    {
        string word;
        cin>>word;
        int x = autoComplete(root, word);
        cout<<autoComp.size()<<endl;
        for(auto it:autoComp)
            cout<<it<<endl;
    }
    if(ch==3)
    {
        string word;
        cin>>word;
        int level=0;
        char str[100];
        autoCorrect(root, word, str, level);
        cout<<autoCorr.size()<<endl;
        for(auto it:autoCorr)
            cout<<it<<endl;
    }
    return 0;
}
