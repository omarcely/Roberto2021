
module Main(o_Tx, o_Frame_Indicator, o_led, o_XLK, i_D,  i_PLK, i_Clk, i_VS, i_HS);

input [7:0]i_D;
output o_XLK, o_Tx;
output reg o_Frame_Indicator;
output [1:0]o_led;
input i_PLK, i_Clk, i_VS, i_HS;
   
///////Define finite states
localparam Waiting = 2'b00;
localparam SendingBytes = 2'b01;
localparam BytesWereSended = 2'b10;

////Define Number of Bytes
localparam BytesPerFrame = 9216;
localparam ClockCountsPerByte = 16275; 
        
        
wire s_Enable_Read;
wire [7:0] s_RAM_Input;
wire [14:0] s_Write_Adress;

reg s_Enable_Write;
reg s_Enable_Tx;
reg [7:0] s_RAM_Output;
reg [14:0] s_Read_Adress;
reg [13:0]s_Byte_Count = 14'b0;
reg [14:0] s_Current_Clock_Count = 0;


reg [1:0]s_Current_State = Waiting;
reg [1:0]s_Next_State = Waiting;



RAM20k RAM (s_RAM_Output, 
            s_Write_Adress, 
            s_Read_Adress, 
            s_RAM_Input, 
            s_Enable_Read, 
            s_Enable_Write, 
            i_Clk);
            
ReadImage Image (o_XLK, 
                 s_RAM_Input, 
                 s_Write_Adress, 
                 s_Enable_Write, 
                 i_D, 
                 i_PLK, 
                 i_Clk, 
                 i_VS, 
                 i_HS);
                 
Tx Transmiter(i_Clk, 
              s_Enable_Tx, 
              s_RAM_Output, 
              o_led[0], 
              o_Tx, 
              o_led[1]);    

//////Check if all the bytes of a frame were loaded

/*always @(posedge i_Clk) begin
    if((~i_VS) & i_HS) begin
        FrameWasReaded = 1;
    end
    else begin
        FrameWasReaded = 0;
    end
          
end*/

//Transitions between states

always @(s_Current_State, i_VS, i_HS, s_Byte_Count) begin
    case(s_Current_State)
        Waiting:
                begin                              
                    if(i_VS==0)begin
                        s_Next_State = Waiting;
                    end
                    else begin
                        s_Next_State = SendingBytes;
                    end
                end
        SendingBytes:
                begin
                    if(s_Byte_Count< BytesPerFrame)begin
                        s_Next_State = SendingBytes;
                    end
                    else begin
                        s_Next_State = BytesWereSended;
                    end
                end
        BytesWereSended:
                begin
                    if(i_VS==1)begin
                        s_Next_State = BytesWereSended;
                    end
                    else begin
                        s_Next_State = Waiting;
                    end
                end
     endcase
end



always @(posedge i_Clk) begin
    case(s_Current_State)
        Waiting:
                begin
                    s_Byte_Count = 0;
                end
        SendingBytes:
                begin
                    if(s_Current_Clock_Count <  10850)begin
                        s_Next_State = SendingBytes;
                    end
                    else begin
                        s_Next_State = BytesWereSended;
                    end
                end
        BytesWereSended:
                begin
                    s_Byte_Count = 0;
                end
     endcase
end
/////

endmodule
