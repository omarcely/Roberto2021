module Enviar(
    input [3:0]sw,
    input Clk,
    output tx,
    output [1:0]led
    );
    
   reg send;
    reg [26:0]count = 0;
    Tx Transmisor(.i_Clock(Clk),
   .i_Tx_DV(send),
   .i_Tx_Byte({sw[3:0],sw[3:0]}), 
   .o_Tx_Active(led[0]),
   .o_Tx_Serial(tx),
   .o_Tx_Done(led[1]));
   
   always @(posedge Clk)
   begin
        if(count<27'd125000000)
        begin
            count <=count + 1;
            send <=0;
        end
        else if(count<27'd125000010)
        begin
            send <=1;
            count <=count + 1;
        end
        else
        begin
            count <=0;
            send <=0;
        end
   end
/*    input rx,
    output tx,
    output [3:0]led    
);

    wire [7:0]Mensaje; 
    wire dv;
 Rx recibir(
   .i_Clock(Clk),
   .i_Rx_Serial(rx),
   .o_Rx_DV(dv),
   .o_Rx_Byte(Mensaje));
   assign led = Mensaje[3:0];
   */
endmodule
/* Codigo pa enviar
    input [3:0]sw,
    input Clk,
    output tx,
    output [1:0]led
    );
    
    reg [7:0]in = 0;
    reg send;
    reg [24:0]count;
    Tx  #(.CLKS_PER_BIT(3472)) Transmisor(.i_Clock(Clk),
   .i_Tx_DV(send),
   .i_Tx_Byte(in), 
   .o_Tx_Active(led[0]),
   .o_Tx_Serial(tx),
   .o_Tx_Done(led[1]));
   
   always @(posedge Clk)
   begin
        if(count<25'd30000000)
        begin
            count <=count + 1;
            send <=0;
        end
        else if(count<25'd30000001)
        begin
            send <=1;
            in <= in + 1;
            count <=count + 1;
        end
        else
        begin
            count <=0;
            send <=0;
        end
   end
   
   
   */


/*
`timescale 1ns/1ps
module uart_tb ();
 
  // Testbench uses a 33,333 MHz clock 
  // Want to interface to 115200 baud UART
  // 33333333 / 115200 = 289 Clocks Per Bit.
  
  
  
  parameter c_CLOCK_PERIOD_NS = 30;
  parameter c_CLKS_PER_BIT    = 289;
  parameter c_BIT_PERIOD      = 8670;
  parameter run_Simulation_time = c_BIT_PERIOD;
   
  reg r_Clock = 0;
  reg r_Tx_DV = 0;
  wire w_Tx_Done;
  reg [7:0] r_Tx_Byte = 0;
  reg r_Rx_Serial = 1;
  wire tx_serial;
  wire [7:0] w_Rx_Byte;
   
 
  // Takes in input byte and serializes it 
  task UART_WRITE_BYTE;
    input [7:0] i_Data;
    integer     ii;
    begin
       
      // Send Start Bit
      r_Rx_Serial <= 1'b0;
      #(c_BIT_PERIOD);
      #1000;
       
       
      // Send Data Byte
      for (ii=0; ii<8; ii=ii+1)
        begin
          r_Rx_Serial <= i_Data[ii];
          #(c_BIT_PERIOD);
        end
       
      // Send Stop Bit
      r_Rx_Serial <= 1'b1;
      #(c_BIT_PERIOD);
     end
  endtask // UART_WRITE_BYTE
   
  // uart_rx example (i_Clock,i_Rx_Serial,o_RX_DV,[7:0] o_Rx_Byte)
   
  Rx #(.CLKS_PER_BIT(c_CLKS_PER_BIT)) UART_RX_INST
    (.i_Clock(r_Clock),
     .i_Rx_Serial(r_Rx_Serial),
     .o_Rx_DV(),
     .o_Rx_Byte(w_Rx_Byte)
     );
   
  // uart_tx example (i_Clock,i_Tx_DV,[7:0] i_Tx_ Byte,o_Tx_Active, o_Tx_Serial, o_Tx_Done)
  Tx #(.CLKS_PER_BIT(c_CLKS_PER_BIT)) UART_TX_INST
    (.i_Clock(r_Clock),
     .i_Tx_DV(r_Tx_DV),
     .i_Tx_Byte(r_Tx_Byte),
     .o_Tx_Active(),
     .o_Tx_Serial(tx_serial),//////////////////////////////////////////////////
     .o_Tx_Done(w_Tx_Done)
     );
 
  always
    #(c_CLOCK_PERIOD_NS/2) r_Clock <= !r_Clock;
 
   
  // Main Testing:
  initial
    begin
       
      // Tell UART to send a command (exercise Tx)
      $dumpfile("dump.vcd");
      $dumpvars;
      @(posedge r_Clock);
      @(posedge r_Clock);
      r_Tx_DV <= 1'b1;
      r_Tx_Byte <= 8'b10101010;
      @(posedge r_Clock);
      r_Tx_DV <= 1'b0;
      @(posedge w_Tx_Done);
       
      // Send a command to the UART (exercise Rx)
      @(posedge r_Clock);
      UART_WRITE_BYTE(8'h3F);
      @(posedge r_Clock);
             
      // Check that the correct command was received
      if (w_Rx_Byte == 8'h3F)
        $display("Test Passed - Correct Byte Received");
      else
        $display("Test Failed - Incorrect Byte Received");
      
      #(10*run_Simulation_time);
      #8000;
      $finish;
      
    end
   
endmodule
*/