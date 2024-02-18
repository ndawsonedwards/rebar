#ifndef ERRORS_H
#define ERRORS_H

typedef enum
{

    Error_None = 0,

    Error_BadParameter,

    Error_BadState,

    Error_IllegalPointer,

    Error_Timeout,

    Error_CrcFailure,
         
    Error_InsufficientMemory,
         
    Error_NotFound, 
         
    Error_AlreadyExists,    
         
    Error_ResourceInUse,        
     
    Error_NotSupported,      
    
    Error_InvalidResponse,

    Error_SystemApiFailed,
    
    Error_CorruptionDetected,
    
    Error_OperationCancelled,
    
    Error_RequestFailed,

    Error_DeviceNotPresentOrResponding,   
    
    Error_NegativeAcknowledgement,

    Error_BufferOverrun,   
    
    Error_InvalidMeasurement,  

    Error_InvalidFormat,      
    
    Error_InvalidLength,        
       
    Error_Parity,
          
    Error_Framing,        
           
    Error_UnsupportedVersion,
         
    Error_UnsupportedType,    
        
    Error_HardwareFailure,      
          
    Error_UnknownHost,      

    Error_OutOfBounds,

    Error_Unknown,

}Error;

#endif