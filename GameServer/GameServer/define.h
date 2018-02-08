#pragma once


#ifndef NULL
#define  NULL   0
#endif


#define  SAFE_DELETE(p)     if(p!=NULL){delete p; p = NULL;}

#define  INVALID_ID                      -1
#define  INVALID_VALUE                   -1