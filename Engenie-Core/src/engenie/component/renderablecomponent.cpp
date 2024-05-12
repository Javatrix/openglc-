#include "engenie/component/renderablecomponent.hpp"
#include "engenie/component/component.hpp"
#include "engenie/entity.hpp"
#include "engenie/shader.hpp"
#include "glm/detail/type_mat.hpp"
#include "glm/detail/type_vec.hpp"
#include "glm/gtc/matrix_transform.hpp"

Entity *parent = nullptr;

RenderableComponent::RenderableComponent(Mesh &mesh, Shader &program)
    : m_mesh(mesh), shader(program) {}
void RenderableComponent::render() {
  if (parent == nullptr)
    return;

  shader.use();

  glm::mat4 model = glm::mat4(1.0f);
  glm::vec3 lerpedRotation = parent->transform.getInterpolatedRotation();
  model = glm::rotate(model, lerpedRotation.x, glm::vec3(1, 0, 0));
  model = glm::rotate(model, lerpedRotation.y, glm::vec3(0, 1, 0));
  model = glm::rotate(model, lerpedRotation.z, glm::vec3(0, 0, 1));
  model = glm::scale(model, parent->transform.getInterpolatedScale());
  model = glm::translate(model, parent->transform.getInterpolatedPosition());
  shader.setMat4("model", model);
  m_mesh.render();
}

void RenderableComponent::updateParent(Entity *entity) { parent = entity; };