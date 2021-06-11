
module Main(o_Tx, o_Frame_Indicator, o_led, o_XLK, i_D,  i_PLK, Clk, i_VS, i_HS, i_RX);

input [7:0]i_D;
output o_XLK, o_Tx;
output reg o_Frame_Indicator;
output [1:0]o_led;
input i_PLK, Clk, i_VS, i_HS, i_RX;

///////Define finite states
localparam Waiting = 2'b00;
localparam SendingBytes = 2'b01;
localparam BytesWereSended = 2'b10;

////Define Number of Bytes
localparam  ClockCountsPerBit = 1085;
localparam ClockCountsPerByte = 11935;   ////Eleven times the number of Clock Counts Per Bit (10 for the bytes an one wxtra for the microcontroller to detect the change of Byte)
localparam BytesPerFrame = 9216;
localparam  ClockCountsForControlSignal = 62500000;

wire w_Enable_Read;
wire [7:0] w_RAM_Input;
wire [7:0] w_RAM_Output;
wire [14:0] w_Write_Adress;
wire r_Enable_Write;


reg r_Enable_Tx = 0;
reg [14:0] r_Read_Adress = 15'b0;
reg [25:0] r_Current_Clock_Count = 0;    /////// [14:0]

reg [1:0]r_Current_State = Waiting;
reg [1:0]r_Next_State = Waiting;



RAM20k RAM (w_RAM_Output,
            w_Write_Adress,
            r_Read_Adress,
            w_RAM_Input,
            w_Enable_Read,
            w_Enable_Write,
            i_PLK);

ReadImage Image (o_XLK,
                 w_RAM_Input,
                 w_Write_Adress,
                 w_Enable_Write,
                 i_D,
                 i_PLK,
                 Clk,
                 i_VS,
                 i_HS);

Tx Transmiter(Clk,
              r_Enable_Tx,
              w_RAM_Output,
              o_led[0],
              o_Tx,
              o_led[1]);


  always @(posedge Clk) begin

    r_Current_State <= r_Next_State;

    case(r_Current_State)
      Waiting: begin
        r_Enable_Tx <= 1'b0;
        r_Read_Adress <= 1'b0;

        if(i_VS==0)begin
          r_Next_State <= Waiting;
          r_Current_Clock_Count <= 1'b0;
          o_Frame_Indicator <= 1'b1;
        end
        else begin
          if (r_Current_Clock_Count < ClockCountsForControlSignal) begin
            r_Current_Clock_Count <= r_Current_Clock_Count + 1;
            r_Next_State = Waiting;
            o_Frame_Indicator <= 1'b0;
          end else begin
            r_Current_Clock_Count <= 1'b0;
            r_Next_State = SendingBytes;
            o_Frame_Indicator <= 1'b0;
          end
        end

      end ///End of Waiting


      SendingBytes: begin
        o_Frame_Indicator <= 1'b0;

        if(r_Current_Clock_Count <  ClockCountsPerBit) begin
          r_Current_Clock_Count <= r_Current_Clock_Count + 1;
          r_Enable_Tx <= 1'b1;
          r_Next_State <= SendingBytes;
          r_Read_Adress <= r_Read_Adress;
        end
        else begin
          if (r_Current_Clock_Count <  ClockCountsPerBit) begin
            r_Current_Clock_Count <= r_Current_Clock_Count + 1;
            r_Enable_Tx <= 1'b0;
            r_Next_State <= SendingBytes;
            r_Read_Adress <= r_Read_Adress;
          end else begin
            if (r_Read_Adress < BytesPerFrame) begin
              r_Current_Clock_Count <= 0;
              r_Enable_Tx <= 1'b0;
              r_Next_State <= SendingBytes;
              r_Read_Adress <= r_Read_Adress + 1;
            end else begin
              r_Current_Clock_Count <= 0;
              r_Enable_Tx <= 1'b0;
              r_Next_State <= BytesWereSended;
              r_Read_Adress <= 1'b0;
            end

          end
        end
      end  ///End of SendingBytes


      BytesWereSended: begin
        r_Enable_Tx <= 1'b0;
        r_Read_Adress <= 1'b0;

        if(r_Current_Clock_Count < ClockCountsForControlSignal)begin
          r_Next_State <= BytesWereSended;
          r_Current_Clock_Count <= r_Current_Clock_Count + 1;
          o_Frame_Indicator <= 0;
        end
        else begin
          r_Current_Clock_Count <= 1'b0;
          r_Next_State <= Waiting;
          o_Frame_Indicator <= 1;
        end
      end ///End of BytesWereSended

    endcase


  end


endmodule
