int sockMerchant(int n, vector<int> ar) {
    int ret = 0;

    for (int i = 0; i < ar.size(); ++i)
    {
        if (ar[i] == -1)
            continue;
        for (int j = i + 1; j < ar.size(); ++j)
        {
            //if (j == i)
             //   continue;
            
            if (ar[i] == ar[j])
            {
                ret += 1;
                ar[j] = -1;
                ar[i] = -1;
                break;
            }        
        }
    }

    return ret;


}
