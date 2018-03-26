// Library incldues
#include <bento_base/security.h>

// Engine includes
#include "core/sugarinstance.h"
#include "core/mesh.h"

namespace donut
{
	TSugarInstance::TSugarInstance()
	{

	}

	TSugarInstance::~TSugarInstance()
	{

	}

	void TSugarInstance::AddMesh(TMesh* _mesh)
	{
		m_meshes.push_back(_mesh);
	}

	TMesh* TSugarInstance::GetMesh(int _meshIndex)
	{
		assert(_meshIndex < m_meshes.size());
		return m_meshes[_meshIndex];
	}

	// Evaluate the sugar instance
	void TSugarInstance::Evaluate(TCollector& _collector, const bento::Matrix4& _tm)
	{
		for (auto& mesh : m_meshes)
		{
			mesh->Evaluate(_collector, _tm);
		}
	}
}