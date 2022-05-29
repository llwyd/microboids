#ifndef _BUFFER_H_
#define _BUFFER_H_

void Task_Flush( void );
void Task_Add( void ( *fn)( void ) );
void Task_Get( void );

#endif /* _BUFFER_H_ */
