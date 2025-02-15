#include "RE/N/NiAVObject.h"

#include "RE/B/BSEffectShaderData.h"
#include "RE/B/BSGeometry.h"
#include "RE/B/BSLightingShaderMaterialFacegenTint.h"
#include "RE/B/BSLightingShaderMaterialHairTint.h"
#include "RE/B/BSLightingShaderProperty.h"
#include "RE/B/BSShaderMaterial.h"
#include "RE/B/BSShaderProperty.h"
#include "RE/B/BSTSmartPointer.h"
#include "RE/B/BSVisit.h"
#include "RE/B/BSXFlags.h"
#include "RE/B/bhkNiCollisionObject.h"
#include "RE/B/bhkRigidBody.h"
#include "RE/H/hkpRigidBody.h"
#include "RE/N/NiColor.h"
#include "RE/N/NiNode.h"
#include "RE/N/NiProperty.h"
#include "RE/N/NiRTTI.h"
#include "RE/S/State.h"

namespace RE
{
	NiAVObject* NiAVObject::Clone()
	{
		using func_t = decltype(&NiAVObject::Clone);
		static REL::Relocation<func_t> func{ RELOCATION_ID(68835, 70187) };
		return func(this);
	}

	void NiAVObject::CullGeometry(bool a_cull)
	{
		BSVisit::TraverseScenegraphGeometries(this, [&](BSGeometry* a_geo) -> BSVisit::BSVisitControl {
			a_geo->SetAppCulled(a_cull);

			return BSVisit::BSVisitControl::kContinue;
		});
	}

	void NiAVObject::CullNode(bool a_cull)
	{
		BSVisit::TraverseScenegraphObjects(this, [&](NiAVObject* a_object) -> BSVisit::BSVisitControl {
			a_object->SetAppCulled(a_cull);

			return BSVisit::BSVisitControl::kContinue;
		});
	}

	bool NiAVObject::GetAppCulled() const
	{
		return flags.all(Flag::kHidden);
	}

	bhkCollisionObject* NiAVObject::GetCollisionObject() const
	{
		using func_t = decltype(&NiAVObject::GetCollisionObject);
		static REL::Relocation<func_t> func{ RELOCATION_ID(25482, 26022) };
		return func(this);
	}

	COL_LAYER NiAVObject::GetCollisionLayer() const
	{
		const auto colObj = collisionObject ? collisionObject->AsBhkNiCollisionObject() : nullptr;
		const auto rigidBody = colObj && colObj->body ? colObj->body->AsBhkRigidBody() : nullptr;

		if (rigidBody && rigidBody->referencedObject) {
			if (const auto havokRigidBody = static_cast<hkpRigidBody*>(rigidBody->referencedObject.get())) {
				if (const auto collidable = havokRigidBody->GetCollidable()) {
					return collidable->GetCollisionLayer();
				}
			}
		}

		return COL_LAYER::kUnidentified;
	}

	BSGeometry* NiAVObject::GetFirstGeometryOfShaderType(BSShaderMaterial::Feature a_type)
	{
		BSGeometry* firstGeometry = nullptr;

		BSVisit::TraverseScenegraphGeometries(this, [&](BSGeometry* a_geometry) -> BSVisit::BSVisitControl {
			auto effect = a_geometry->properties[BSGeometry::States::kEffect];
			auto lightingShader = netimmerse_cast<BSLightingShaderProperty*>(effect.get());
			if (lightingShader) {
				if (a_type == BSShaderMaterial::Feature::kNone) {
					firstGeometry = a_geometry;
					return BSVisit::BSVisitControl::kStop;
				}
				const auto material = lightingShader->material;
				if (material && material->GetFeature() == a_type) {
					firstGeometry = a_geometry;
					return BSVisit::BSVisitControl::kStop;
				}
			}

			return BSVisit::BSVisitControl::kContinue;
		});

		return firstGeometry;
	}

	float NiAVObject::GetMass()
	{
		float mass = 0.0f;

		BSVisit::TraverseScenegraphCollision(this, [&](bhkNiCollisionObject* a_col) -> BSVisit::BSVisitControl {
			if (auto hkpBody = a_col->body ? static_cast<RE::hkpRigidBody*>(a_col->body->referencedObject.get()) : nullptr) {
				mass += hkpBody->motion.GetMass();
			}
			return BSVisit::BSVisitControl::kContinue;
		});

		return mass;
	}

	TESObjectREFR* NiAVObject::GetUserData() const
	{
		if (userData) {
			return userData;
		}

		if (parent) {
			return parent->GetUserData();
		}

		return nullptr;
	}

	bool NiAVObject::HasAnimation() const
	{
		const auto bsxFlags = GetExtraData<BSXFlags>("BSX");
		return bsxFlags && ((bsxFlags->value & 2) != 0);
	}

	bool NiAVObject::HasShaderType(BSShaderMaterial::Feature a_type)
	{
		bool hasShaderType = false;

		BSVisit::TraverseScenegraphGeometries(this, [&](BSGeometry* a_geometry) -> BSVisit::BSVisitControl {
			auto effect = a_geometry->properties[BSGeometry::States::kEffect];
			auto lightingShader = netimmerse_cast<BSLightingShaderProperty*>(effect.get());
			if (lightingShader) {
				auto material = lightingShader->material;
				if (material && material->GetFeature() == a_type) {
					hasShaderType = true;
					return BSVisit::BSVisitControl::kStop;
				}
			}
			return BSVisit::BSVisitControl::kContinue;
		});

		return hasShaderType;
	}

	void NiAVObject::RemoveDecals()
	{
		using func_t = decltype(&NiAVObject::RemoveDecals);
		static REL::Relocation<func_t> func{ RELOCATION_ID(15547, 15723) };
		return func(this);
	}

	void NiAVObject::SetAppCulled(bool a_cull)
	{
		a_cull ? flags.set(Flag::kHidden) : flags.reset(Flag::kHidden);
	}

	void NiAVObject::SetCollisionLayer(COL_LAYER a_collisionLayer)
	{
		using func_t = decltype(&NiAVObject::SetCollisionLayer);
		static REL::Relocation<func_t> func{ RELOCATION_ID(76170, 77998) };
		return func(this, a_collisionLayer);
	}

	void NiAVObject::SetCollisionLayerAndGroup(COL_LAYER a_collisionLayer, std::uint32_t a_group)
	{
		using func_t = decltype(&NiAVObject::SetCollisionLayerAndGroup);
		static REL::Relocation<func_t> func{ RELOCATION_ID(76171, 77999) };
		return func(this, a_collisionLayer, a_group);
	}

	bool NiAVObject::SetMotionType(hkpMotion::MotionType a_motionType, bool a_recurse, bool a_force, bool a_allowActivate)
	{
		using func_t = decltype(&NiAVObject::SetMotionType);
		static REL::Relocation<func_t> func{ Offset::NiAVObject::SetMotionType };
		return func(this, a_motionType, a_recurse, a_force, a_allowActivate);
	}

	bool NiAVObject::SetProjectedUVData(const NiColorA& a_projectedUVParams, const NiColor& a_projectedUVColor, bool a_isSnow)
	{
		bool result = false;

		BSVisit::TraverseScenegraphGeometries(this, [&](BSGeometry* a_geometry) -> BSVisit::BSVisitControl {
			using Flag = BSShaderProperty::EShaderPropertyFlag;
			using Flag8 = BSShaderProperty::EShaderPropertyFlag8;
			using Feature = BSShaderMaterial::Feature;

			auto effect = a_geometry->properties[BSGeometry::States::kEffect];
			auto lightingShader = netimmerse_cast<BSLightingShaderProperty*>(effect.get());
			if (lightingShader) {
				if (lightingShader->flags.any(Flag::kSkinned) || lightingShader->flags.any(Flag::kTreeAnim) || lightingShader->flags.any(Flag::kBackLighting)) {
					return BSVisit::BSVisitControl::kContinue;
				}

				if (const auto material = lightingShader->material; material) {
					if (const auto feature = material->GetFeature(); feature == Feature::kParallax || feature == Feature::kMultilayerParallax || feature == Feature::kFaceGen || feature == Feature::kMultiTexLand) {
						return BSVisit::BSVisitControl::kContinue;
					}
				}

				result = true;

				lightingShader->SetFlags(Flag8::kProjectedUV, true);
				if (a_isSnow) {
					lightingShader->SetFlags(Flag8::kSnow, true);
				}

				lightingShader->projectedUVParams = a_projectedUVParams;
				lightingShader->projectedUVColor = a_projectedUVColor;

				lightingShader->SetupGeometry(a_geometry);
			}
			return BSVisit::BSVisitControl::kContinue;
		});

		return result;
	}

	void NiAVObject::TintScenegraph(const NiColorA& a_color)
	{
		auto                                gState = BSGraphics::State::GetSingleton();
		BSTSmartPointer<BSEffectShaderData> newShaderData(new BSEffectShaderData());
		newShaderData->fillColor = a_color;
		newShaderData->baseTexture = gState->defaultTextureWhite;

		BSVisit::TraverseScenegraphGeometries(this, [&](BSGeometry* a_geometry) -> BSVisit::BSVisitControl {
			auto effect = a_geometry->properties[BSGeometry::States::kEffect];
			auto shaderProp = netimmerse_cast<BSShaderProperty*>(effect.get());
			if (shaderProp && shaderProp->AcceptsEffectData()) {
				auto shaderData = shaderProp->effectData;
				if (!shaderData || shaderData->baseTexture == gState->defaultTextureWhite) {
					shaderProp->SetEffectShaderData(newShaderData);
				}
			}

			return BSVisit::BSVisitControl::kContinue;
		});
	}

	void NiAVObject::Update(NiUpdateData& a_data)
	{
		using func_t = decltype(&NiAVObject::Update);
		static REL::Relocation<func_t> func{ Offset::NiAVObject::Update };
		return func(this, a_data);
	}

	void NiAVObject::UpdateBodyTint(const NiColor& a_color)
	{
		BSVisit::TraverseScenegraphGeometries(this, [&](BSGeometry* a_geometry) -> BSVisit::BSVisitControl {
			using State = BSGeometry::States;
			using Feature = BSShaderMaterial::Feature;

			auto effect = a_geometry->properties[State::kEffect].get();
			if (effect) {
				auto lightingShader = netimmerse_cast<BSLightingShaderProperty*>(effect);
				if (lightingShader) {
					auto material = lightingShader->material;
					if (material && material->GetFeature() == Feature::kFaceGenRGBTint) {
						auto facegenTint = static_cast<BSLightingShaderMaterialFacegenTint*>(material);
						facegenTint->tintColor = a_color;
					}
				}
			}

			return BSVisit::BSVisitControl::kContinue;
		});
	}

	void NiAVObject::UpdateHairColor(const NiColor& a_color)
	{
		BSVisit::TraverseScenegraphGeometries(this, [&](BSGeometry* a_geometry) -> BSVisit::BSVisitControl {
			using State = BSGeometry::States;
			using Feature = BSShaderMaterial::Feature;

			auto effect = a_geometry->properties[State::kEffect].get();
			if (effect) {
				auto lightingShader = netimmerse_cast<BSLightingShaderProperty*>(effect);
				if (lightingShader) {
					auto material = lightingShader->material;
					if (material && material->GetFeature() == Feature::kHairTint) {
						auto hairTint = static_cast<BSLightingShaderMaterialHairTint*>(material);
						hairTint->tintColor = a_color;
					}
				}
			}

			return BSVisit::BSVisitControl::kContinue;
		});
	}

	void NiAVObject::UpdateMaterialAlpha(float a_alpha, bool a_doOnlySkin)
	{
		BSVisit::TraverseScenegraphGeometries(this, [&](BSGeometry* a_geometry) -> BSVisit::BSVisitControl {
			using State = BSGeometry::States;
			using Feature = BSShaderMaterial::Feature;

			auto effect = a_geometry->properties[State::kEffect].get();
			if (effect) {
				auto lightingShader = netimmerse_cast<BSLightingShaderProperty*>(effect);
				if (lightingShader) {
					auto material = static_cast<BSLightingShaderMaterialBase*>(lightingShader->material);
					if (material) {
						if (a_doOnlySkin) {
							if (auto const feature = material->GetFeature(); feature != Feature::kFaceGen && feature != Feature::kFaceGenRGBTint) {
								return BSVisit::BSVisitControl::kContinue;
							}
						}
						material->materialAlpha = a_alpha;
					}
				}
			}

			return BSVisit::BSVisitControl::kContinue;
		});
	}

	void NiAVObject::UpdateRigidConstraints(bool a_enable, std::uint8_t a_arg2, std::uint32_t a_arg3)
	{
		using func_t = decltype(&NiAVObject::UpdateRigidConstraints);
		static REL::Relocation<func_t> func{ RELOCATION_ID(76271, 78103) };
		return func(this, a_enable, a_arg2, a_arg3);
	}
}
