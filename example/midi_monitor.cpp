/*=============================================================================
   Copyright (c) 2014-2018 Joel de Guzman. All rights reserved.

   Distributed under the MIT License [ https://opensource.org/licenses/MIT ]
=============================================================================*/
#include <q_io/midi_stream.hpp>
#include <iostream>

namespace q = cycfi::q;
namespace midi = q::midi;

///////////////////////////////////////////////////////////////////////////////
// MIDI processor example. Simply monitors the incoming MIDI stream
// and prints the event to std::cout. Not all events are monitored.
///////////////////////////////////////////////////////////////////////////////

struct midi_processor : midi::processor
{
   using midi::processor::operator();

   void operator()(midi::note_off msg, std::size_t time)
   {
      std::cout
         << "Note On  {"
         << "Channel: "    << int(msg.channel())
         << ", Key: "      << int(msg.key())
         << ", Velocity: " << int(msg.velocity())
         << '}'            << std::endl;
   }

   void operator()(midi::note_on msg, std::size_t time)
   {
      std::cout
         << "Note Off {"
         << "Channel: "    << int(msg.channel())
         << ", Key: "      << int(msg.key())
         << ", Velocity: " << int(msg.velocity())
         << '}'            << std::endl;
   }

   void operator()(midi::poly_aftertouch msg, std::size_t time)
   {
      std::cout
         << "Polyphonic Aftertouch {"
         << "Channel: "    << int(msg.channel())
         << ", Key: "      << int(msg.key())
         << ", Pressure: " << int(msg.pressure())
         << '}'            << std::endl;
   }

   void operator()(midi::control_change msg, std::size_t time)
   {
      std::cout
         << "Control Change {"
         << "Channel: "       << int(msg.channel())
         << ", Controller: "  << int(msg.controller())
         << ", Value: "       << int(msg.value())
         << '}'               << std::endl;
   }

   void operator()(midi::program_change msg, std::size_t time)
   {
      std::cout
         << "Program Change {"
         << "Channel: "    << int(msg.channel())
         << ", Preset: "   << int(msg.preset())
         << '}'            << std::endl;
   }

   void operator()(midi::channel_aftertouch msg, std::size_t time)
   {
      std::cout
         << "Channel Aftertouch {"
         << "Channel: "    << int(msg.channel())
         << ", Pressure: " << int(msg.pressure())
         << '}'            << std::endl;
   }

   void operator()(midi::pitch_bend msg, std::size_t time)
   {
      std::cout
         << "Pitch Bend             {"
         << "Channel: "    << int(msg.channel())
         << ", Value: "    << int(msg.value())
         << '}'            << std::endl;
   }
};

int main()
{
   auto midi_devices = q::midi_device::list();
   if (midi_devices.size() == 0)
      return 0;

   q::midi_input_stream stream(midi_devices[0]);

   while (true)
      stream.process(midi_processor{});

   return 0;
}
