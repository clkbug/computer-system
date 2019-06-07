package y86_64

import chisel3._
import chisel3.iotesters
import chisel3.iotesters.{ChiselFlatSpec, Driver, PeekPokeTester}

class CPUMain {

}

class RegisterFileTester(rf: RegisterFile) extends PeekPokeTester(rf) {
  private def rd(addr: Int, data: Int) = {
    poke(rf.io.regA, addr)
    poke(rf.io.regAEnable, 1)
    step(1)
    expect(rf.io.regAData, data)
  }

  private def wr(addr: Int, data: Int) = {
    poke(rf.io.regMEnable, 1)
    poke(rf.io.regM, addr)
    poke(rf.io.regMData, data)
    step(1)
  }

  wr(0, 1)
  rd(0, 1)
  wr(9, 11)
  rd(9, 11)
}


object RegisterFileMain extends App {
  iotesters.Driver.execute(args, () => new RegisterFile) {
    c => new RegisterFileTester(c)
  }
}
