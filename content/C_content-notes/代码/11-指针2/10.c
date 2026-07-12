


calloc 用来分配n个元素，且每个元素占size字节，总分配的大小：n*size
    calloc 不仅会分配卡紧，并且会把分配的空间清0，
     void *calloc(size_t nmemb, size_t size);
        nmemb：要分配多少个元素
        size：每个元素的所占的字节大小
    
    返回值：
        成功返回分配的空间的首地址
        失败返回NULL；