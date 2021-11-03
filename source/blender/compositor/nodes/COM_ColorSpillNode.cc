/*
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * Copyright 2011, Blender Foundation.
 */

#include "COM_ColorSpillNode.h"
#include "COM_ColorSpillOperation.h"

namespace blender::compositor {

ColorSpillNode::ColorSpillNode(bNode *editor_node) : Node(editor_node)
{
  /* pass */
}

void ColorSpillNode::convert_to_operations(NodeConverter &converter,
                                           const CompositorContext & /*context*/) const
{
  bNode *editorsnode = get_bnode();

  NodeInput *input_socket_image = this->get_input_socket(0);
  NodeInput *input_socket_fac = this->get_input_socket(1);
  NodeOutput *output_socket_image = this->get_output_socket(0);

  ColorSpillOperation *operation;
  operation = new ColorSpillOperation();
  operation->set_settings((NodeColorspill *)editorsnode->storage);
  operation->set_spill_channel(editorsnode->custom1 - 1); /* Channel for spilling */
  operation->set_spill_method(editorsnode->custom2);      /* Channel method */
  converter.add_operation(operation);

  converter.map_input_socket(input_socket_image, operation->get_input_socket(0));
  converter.map_input_socket(input_socket_fac, operation->get_input_socket(1));
  converter.map_output_socket(output_socket_image, operation->get_output_socket());
}

}  // namespace blender::compositor
