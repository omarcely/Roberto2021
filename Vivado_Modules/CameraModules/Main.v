
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
localparam ClockCountsPerByte = 11935;
localparam  ClockCountsPerBit = 1085;

wire w_Enable_Read;
wire [7:0] w_RAM_Input;
wire [7:0] w_RAM_Output;
wire [14:0] w_Write_Adress;
wire w_End_Of_Byte_Transmission;


reg r_Enable_Write;
reg r_Enable_Tx = 0;
reg [14:0] r_Read_Adress = 15'b0;
reg [14:0] r_Current_Clock_Count = 0;


reg [1:0]r_Current_State = Waiting;
reg [1:0]r_Next_State = Waiting;



RAM20k RAM (w_RAM_Output,
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
              w_RAM_Output,
              o_led_Tx_Active,
              o_Tx,
              w_End_Of_Byte_Transmission);


  always @(posedge i_Clk) begin

    r_Current_State <= r_Next_State;

    case(r_Current_State)
      Waiting: begin
        r_Current_Clock_Count <= 1'b0;
        r_Enable_Tx <= 1'b0;

        if(i_VS==0)begin
          r_Next_State = Waiting;
        end
        else begin
          r_Next_State = SendingBytes;
        end

      end ///End of Waiting


      SendingBytes: begin
        if(r_Current_Clock_Count <  ClockCountsPerBit) begin
          r_Current_Clock_Count <= r_Current_Clock_Count + 1;
          r_Enable_Tx <= 1'b1;
          r_Next_State <= SendingBytes;
        end
        else begin
          if (r_Current_Clock_Count <  ClockCountsPerBit) begin
            r_Current_Clock_Count <= r_Current_Clock_Count + 1;
            r_Enable_Tx <= 1'b0;
            r_Next_State <= SendingBytes;
          end else begin
            if (r_Read_Adress < BytesPerFrame) begin
              r_Current_Clock_Count <= 0;
              r_Enable_Tx <= 1'b0;
              r_Next_State <= SendingBytes;
            end else begin
              r_Current_Clock_Count <= 0;
              r_Enable_Tx <= 1'b0;
              r_Next_State <= BytesWereSended;
            end

          end
        end
      end  ///End of SendingBytes


      BytesWereSended: begin
        r_Current_Clock_Count <= 1'b0;
        r_Enable_Tx <= 1'b0;

        if(i_VS==1)begin
          r_Next_State = BytesWereSended;
        end
        else begin
          r_Next_State = Waiting;
        end
      end ///End of BytesWereSended

    endcase


  end

  always @ (posedge w_End_Of_Byte_Transmission) begin
    case(r_Current_State)
      Waiting: begin
        r_Read_Adress <= 0;
      end

      SendingBytes: begin
        r_Read_Adress <= r_Read_Adress + 1;
      end

      BytesWereSended: begin
        r_Read_Adress <= 0;
      end

  end


endmodule
