
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "strings.h"


/*********strlen tests*************/

void IsStrelen(){

    char test[10] = "abcdefghij";
    
    
    if(Strlen(test)== strlen(test))
    {
        printf("PASS  ");
        printf("IsStrlen\n");
        return;
    }
    printf("FAIL   ");    
    printf("IsStrlen\n");
    return;
}

void IsStrelenWithSpace(){

    char test[10] = "abcd fghij";
    
    
    if(Strlen(test)== strlen(test))
    {
        printf("PASS  ");
        printf("Is Strlen With Space\n");
        return;
    }
    printf("FAIL   ");    
    printf("Is Strlen With Space\n");
    return;
}

void IsStrelenWithNull(){

    char test[10];
    
    
    if(Strlen(test)== strlen(test))
    {
        printf("PASS  ");
        printf("Is Strlen With NULL\n");
        return;
    }
    printf("FAIL   ");    
    printf("Is Strlen With NULL\n");
    return;
}

void IsStrelenEndInMiddle(){

    char test[10] ="asd\0hfgh";  
    
    if(Strlen(test)== strlen(test))
    {
        printf("PASS  ");
        printf("Is Strlen With \\0\n");
        return;
    }
    printf("FAIL   ");    
    printf("Is Strlen With \\0\n");
    return;
}

/***********************strlen Rec. tests****************************/
void IsStrelenRec(){

    char test[10] = "abcdefghij";
    
    
    if(StrLenRec(test)== strlen(test))
    {
        printf("PASS  ");
        printf("IsStrlen Rec\n");
        return;
    }
    printf("FAIL   ");
    printf("IsStrlen Rec\n");   
    return;
}

void IsStrelenWithSpaceRec(){

    char test[10] = "abcd fghij";   
    
    if(StrLenRec(test)== strlen(test))
    {
        printf("PASS  ");
        printf("Is Strlen Rec. With Space\n");
        return;
    }
    printf("FAIL   ");    
    printf("Is Strlen Rec. With Space\n");
    return;
}

void IsStrelenWithNullRec(){

    char test[10];
    
    
    if(StrLenRec(test)== strlen(test))
    {
        printf("PASS  ");
        printf("Is Strlen Rec. With NULL\n");
        return;
    }
    printf("FAIL   ");    
    printf("Is Strlen Rec. With NULL\n");
    return;
}

void IsStrelenEndInMiddleRec(){

    char test[10] ="asd\0hfgh";  
    
    if(StrLenRec(test)== strlen(test))
    {
        printf("PASS  ");
        printf("Is Strlen Rec. With \\0\n");
        return;
    }
    printf("FAIL   ");    
     printf("Is Strlen Rec. With \\0\n");
    return;
}

/******************StrCompare tests*****************/

void IsCompareEqual(){

    char test1[10] ="asdhfgh"; 
    char test2[10] ="asdhfgh";  
    
    if(StrCompare(test1, test2) == strcmp(test1, test2))
    {
        printf("PASS  ");
        printf("Is Compare Equal\n");
        return;
    }
    printf("FAIL   ");    
    printf("Is Compare Equal\n");
    return;
}

void IsCompareFirstLarger(){

    char test1[10] ="asdcvhfgh"; 
    char test2[10] ="asdafgh";  
    
   if(StrCompare(test1, test2) == 'c' - 'a')
    {
        printf("PASS  ");
        printf("Is Compare First Larger\n");
        return;
    }
    printf("FAIL   ");    
    printf("Is Compare First Larger\n");
    return;
}

void IsCompareSecondLarger(){

    char test1[10] ="asdhfgh"; 
    char test2[10] ="awqsdvfgh";  
    
    if(StrCompare(test1, test2) == 's' - 'w')
    {
        printf("PASS  ");
        printf("Is Compare Second Larger\n");
        return;
    }
    printf("FAIL   ");    
    printf("Is Compare Second Larger\n");
    return;
}

void IsCompareNull(){

    char* test1= NULL;
    char* test2= NULL;
    
    if(StrCompare(test1, test2) == -300)
    {
        printf("PASS  ");
        printf("Is Compare with Null\n");
        return;
    }
    printf("FAIL   ");    
    printf("Is Compare with Null\n");
    return;
}

/******************StrCompare Rec. tests****************/
void IsCompareEqualRec(){

    char test1[10] ="asdhfgh"; 
    char test2[10] ="asdhfgh";  
    
    if( StrCompareRec(test1, test2) == strcmp(test1, test2))
    {
        printf("PASS  ");
        printf("Is Compare Equal Rec\n");
        return;
    }
    printf("FAIL   ");    
    printf("Is Compare Equal Rec\n");
    return;
}

void IsCompareFirstLargerRec(){

    char* test1 ="zsdgvhfgh"; 
    char* test2="asdafgh";  
    
   if( StrCompareRec(test1, test2) == 'z' - 'a')
    {
        printf("PASS  ");
        printf("Is Compare First LargerRec\n");
        return;
    }
    printf("FAIL   ");    
    printf("Is Compare First LargerRec\n");
    return;
}

void IsCompareSecondLargerRec(){

    char test1[10] ="asdhfgh"; 
    char test2[10] ="awqsdvfgh";  
    
    if(StrCompareRec(test1, test2) == 's' - 'w')
    {
        printf("PASS  ");
        printf("Is Compare Second LargerRec\n");
        return;
    }
    printf("FAIL   ");    
    printf("Is Compare Second LargerRec\n");
    return;
}

void IsCompareNullRec(){

    char* test1= NULL;
    char* test2= NULL;
    
    if( StrCompareRec(test1, test2) == -300)
    {
        printf("PASS  ");
        printf("Is Compare with NullRec\n");
        return;
    }
    printf("FAIL   ");    
    printf("Is Compare with NullRec\n");
    return;
}

/******************StrCopy tests***************/

void IsStrcopy(){

    char test1[11] = "abcdefghij";
    char test2[11];    
    StrCopy(test2, test1);
    if(test2[9] == 'j')
    {
        printf("PASS  ");
        printf("IsStrCopy\n");
        return;
    }
    printf("FAIL   ");    
    printf("IsStrCopy\n");
    return;
}

void IsStrcopyWithSpace(){

    char test1[11] = "abcd fghij";
    char test2[11];    
    StrCopy(test2, test1);
    if(test2[9] == 'j')
    {
        printf("PASS  ");
        printf("IsStrCopyWithSpace\n");
        return;
    }
    printf("FAIL   ");    
    printf("IsStrCopyWithSpace\n");
    return;

}

void IsStrcopyWithNull(){

    char* test1 = NULL;
    char* test2= NULL;    
    
    if(StrCopy(test2, test1) == NULL)
    {
        printf("PASS  ");
        printf("IsStrCopyWithNull\n");
        return;
    }
    printf("FAIL   ");    
    printf("IsStrCopyWithNull\n");
    return;
}

void IsStrcopyEndInMiddle(){

    char test1[11] = "abcd\0fghij";
    char test2[11];    
    StrCopy(test2, test1);
    
    if(test2[4] == '\0')
    {
        printf("PASS  ");
        printf("IsStrCopyWithBackslash\n");
        return;
    }
    printf("FAIL   ");    
    printf("IsStrCopyWithBackslash\n");
    return;

}

/******************StrCopy Rec. tests***************/

void IsStrcopyRec(){

    char test1[11] = "abcdefghij";
    char test2[11];    
    StrCopyRec(test2, test1);
    if(test2[9] == 'j')
    {
        printf("PASS  ");
        printf("IsStrCopyRec\n");
        return;
    }
    printf("FAIL   ");    
    printf("IsStrCopyRec\n");
    return;
}

void IsStrcopyWithSpaceRec(){

    char test1[11] = "abcd fghij";
    char test2[11];    
    StrCopyRec(test2, test1);
    if(test2[9] == 'j')
    {
        printf("PASS  ");
        printf("IsStrCopyWithSpaceRec\n");
        return;
    }
    printf("FAIL   ");    
    printf("IsStrCopyWithSpaceRec\n");
    return;

}

void IsStrcopyWithNullRec(){

    char* test1 = NULL;
    char* test2= NULL;    
    
    if(StrCopyRec(test2, test1) == NULL)
    {
        printf("PASS  ");
        printf("IsStrCopyWithNullRec\n");
        return;
    }
    printf("FAIL   ");    
    printf("IsStrCopyWithNullRec\n");
    return;
}

void IsStrcopyEndInMiddleRec(){

    char test1[11] = "abcd\0fghij";
    char test2[11];    
    StrCopyRec(test2, test1);
    
    if(test2[4] == '\0')
    {
        printf("PASS  ");
        printf("IsStrCopyWithBackslashRec\n");
        return;
    }
    printf("FAIL   ");    
    printf("IsStrCopyWithBackslashRec\n");
    return;

}


/*******************strncopy tests******************

void IsStrNcopy(){

    char test1[11] = "abcdefghij";
    char test2[11];    
    StrCopy(test2, test1);
    if(test2[9] == 'j')
    {
        printf("PASS  ");
        printf("IsStrCopy\n");
        return;
    }
    printf("FAIL   ");    
    printf("IsStrCopy\n");
    return;
}

void IsStrcopyWithSpace(){

    char test1[11] = "abcd fghij";
    char test2[11];    
    StrCopy(test2, test1);
    if(test2[9] == 'j')
    {
        printf("PASS  ");
        printf("IsStrCopyWithSpace\n");
        return;
    }
    printf("FAIL   ");    
    printf("IsStrCopyWithSpace\n");
    return;

}

void IsStrcopyWithNull(){

    char* test1 = NULL;
    char* test2= NULL;    
    
    if(StrCopy(test2, test1) == NULL)
    {
        printf("PASS  ");
        printf("IsStrCopyWithNull\n");
        return;
    }
    printf("FAIL   ");    
    printf("IsStrCopyWithNull\n");
    return;
}

void IsStrcopyEndInMiddle(){

    char test1[11] = "abcd\0fghij";
    char test2[11];    
    StrCopy(test2, test1);
    
    if(test2[4] == '\0')
    {
        printf("PASS  ");
        printf("IsStrCopyWithBackslash\n");
        return;
    }
    printf("FAIL   ");    
    printf("IsStrCopyWithBackslash\n");
    return;

}

/******************StrCopy Rec. tests***************/
/*
void IsStrcopyRec(){

    char test1[11] = "abcdefghij";
    char test2[11];    
    StrCopyRec(test2, test1);
    if(test2[9] == 'j')
    {
        printf("PASS  ");
        printf("IsStrCopyRec\n");
        return;
    }
    printf("FAIL   ");    
    printf("IsStrCopyRec\n");
    return;
}

void IsStrcopyWithSpaceRec(){

    char test1[11] = "abcd fghij";
    char test2[11];    
    StrCopyRec(test2, test1);
    if(test2[9] == 'j')
    {
        printf("PASS  ");
        printf("IsStrCopyWithSpaceRec\n");
        return;
    }
    printf("FAIL   ");    
    printf("IsStrCopyWithSpaceRec\n");
    return;

}

void IsStrcopyWithNullRec(){

    char* test1 = NULL;
    char* test2= NULL;    
    
    if(StrCopyRec(test2, test1) == NULL)
    {
        printf("PASS  ");
        printf("IsStrCopyWithNullRec\n");
        return;
    }
    printf("FAIL   ");    
    printf("IsStrCopyWithNullRec\n");
    return;
}

void IsStrcopyEndInMiddleRec(){

    char test1[11] = "abcd\0fghij";
    char test2[11];    
    StrCopyRec(test2, test1);
    
    if(test2[4] == '\0')
    {
        printf("PASS  ");
        printf("IsStrCopyWithBackslashRec\n");
        return;
    }
    printf("FAIL   ");    
    printf("IsStrCopyWithBackslashRec\n");
    return;

}
*/
int main(){

    IsStrelen();
    IsStrelenWithSpace();
    IsStrelenWithNull();
    IsStrelenEndInMiddle();
    
    IsStrelenRec();
    IsStrelenWithSpaceRec();
    IsStrelenWithNullRec();
    IsStrelenEndInMiddleRec();
    
    IsCompareEqual();
    IsCompareFirstLarger();
    IsCompareSecondLarger();
    IsCompareNull();
    
    IsCompareEqualRec();
    IsCompareFirstLargerRec();
    IsCompareSecondLargerRec();
    IsCompareNullRec();
    
    IsStrcopyRec();
    IsStrcopyWithSpaceRec();
    IsStrcopyWithNullRec();
    IsStrcopyEndInMiddleRec();
    
    return 0;
}
