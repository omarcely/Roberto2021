
module Main(o_Tx, o_Frame_Indicator, o_led_Tx_Active, o_XLK, i_D,  i_PLK, i_Clk, i_VS, i_HS);

input [7:0]i_D;
output o_XLK, o_Tx;
output reg o_Frame_Indicator;
output [1:0]o_led_Tx_Active;
input i_PLK, i_Clk, i_VS, i_HS;

///////Define finite states
localparam Waiting = 2'b00;
localparam SendingBytes = 2'b01;
localparam BytesWereSended = 2'b10;

////Define Number of Bytes
localparam BytesPerFrame = 9216;
localparam ClockCountsPerByte = 16275;


wire w_Enable_Read;
wire [7:0] w_RAM_Input;
wire [14:0] w_Write_Adress;
wire w_End_Of_Byte_Transmission;


reg r_Enable_Write;
reg r_Enable_Tx;
reg [7:0] r_RAM_Output;
reg [14:0] r_Read_Adress;
reg [13:0]r_Byte_Count = 14'b0;
reg [14:0] r_Current_Clock_Count = 0;


reg [1:0]r_Current_State = Waiting;
reg [1:0]r_Next_State = Waiting;



RAM20k RAM (r_RAM_Output,
            w_Write_Adress,
            r_Read_Adress,
            w_RAM_Input,
            w_Enable_Read,
            r_Enable_Write,
            i_PLK);

ReadImage Image (o_XLK,
                 w_RAM_Input,
                 w_Write_Adress,
                 r_Enable_Write,
                 i_D,
                 i_PLK,
                 i_Clk,
                 i_VS,
                 i_HS);

Tx Transmiter(i_Clk,
              r_Enable_Tx,
              r_RAM_Output,
              o_led_Tx_Active,
              o_Tx,
              w_End_Of_Byte_Transmission);


  always @(r_Current_State, i_VS, i_HS, r_Byte_Count) begin
    case(r_Current_State)
      Waiting: begin
        if(i_VS==0)begin
          r_Next_State = Waiting;
        end
        else begin
          r_Next_State = SendingBytes;
        end
      end

      SendingBytes: begin
        if(r_Byte_Count< BytesPerFrame)begin
          r_Next_State = SendingBytes;
        end
        else begin
          r_Next_State = BytesWereSended;
        end
      end

      BytesWereSended: begin
        if(i_VS==1)begin
          r_Next_State = BytesWereSended;
        end
        else begin
          r_Next_State = Waiting;
        end
      end

    endcase
  end



  always @(posedge i_Clk) begin
    case(r_Current_State)
      Waiting: begin
        r_Byte_Count = 0;
      end

      SendingBytes: begin
        if(r_Current_Clock_Count <  10850) begin
          
        end
        else begin

        end
      end

      BytesWereSended: begin
        r_Byte_Count = 0;
      end
    endcase
  end


endmodule
