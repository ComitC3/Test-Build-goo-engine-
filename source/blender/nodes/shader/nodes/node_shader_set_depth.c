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
 * The Original Code is Copyright (C) 2005 Blender Foundation.
 * All rights reserved.
 */

#include "../node_shader_util.h"

/* **************** OUTPUT ******************** */

static bNodeSocketTemplate sh_node_set_depth_in[] = {
    {SOCK_SHADER, N_("BSDF")},
    {SOCK_FLOAT, N_("View Depth"), 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, PROP_NONE, SOCK_HIDE_VALUE},
    {-1, ""},
};

static bNodeSocketTemplate sh_node_set_depth_out[] = {
    {SOCK_SHADER, N_("BSDF")},
    {-1, ""},
};

static int node_shader_gpu_set_depth(GPUMaterial *mat,
                                        bNode *node,
                                        bNodeExecData *UNUSED(execdata),
                                        GPUNodeStack *in,
                                        GPUNodeStack *out)
{
  if (!in[1].link) {
    GPU_link(mat, "view_z_get", &in[1].link);
  }

  return GPU_stack_link(mat, node, "node_set_depth", in, out);
}

/* node type definition */
void register_node_type_sh_set_depth(void)
{
  static bNodeType ntype;

  sh_node_type_base(&ntype, SH_NODE_SET_DEPTH, "Set Depth", NODE_CLASS_SHADER, 0);
  node_type_socket_templates(&ntype, sh_node_set_depth_in, sh_node_set_depth_out);
  node_type_size_preset(&ntype, NODE_SIZE_MIDDLE);
  node_type_init(&ntype, NULL);
  node_type_storage(&ntype, "", NULL, NULL);
  node_type_gpu(&ntype, node_shader_gpu_set_depth);

  nodeRegisterType(&ntype);
}
