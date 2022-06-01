<script setup>
import { UserRoleId } from '@/constants'
import { computed, defineEmits, ref, defineExpose } from 'vue'
import { useStore } from 'vuex'

const emit = defineEmits(['submit'])
const store = useStore()

const login = ref('')
const roleId = ref(UserRoleId.MANAGER)
const firstName = ref('')
const lastName = ref('')

const userRoles = computed(() => store.getters.settings.userRoles)

const submitHandler = async (e) => {
  e.preventDefault()

  const user = {
    login: login.value.trim(),
    roleId: roleId.value,
    firstName: firstName.value.trim(),
    lastName: lastName.value.trim(),
  }

  if (!user.login || !user.firstName || !user.lastName) {
    return alert('Заполните все поля')
  }

  emit('submit', user)
}

defineExpose({
  clearForm() {
    login.value = ''
    roleId.value = UserRoleId.MANAGER
    firstName.value = ''
    lastName.value = ''
  },
})
</script>

<template>
  <form class="create-employee-form" @submit="submitHandler">
    <h4>Регистрация сотрудника</h4>

    <div class="form-group">
      <input v-model="login" placeholder="Логин" />
    </div>

    <div class="form-group">
      <select v-model="roleId">
        <option v-for="role in userRoles" :key="role.id" :value="role.id">{{ role.name }}</option>
      </select>
    </div>

    <div class="form-group">
      <input v-model="firstName" placeholder="Имя" />
    </div>

    <div class="form-group">
      <input v-model="lastName" placeholder="Фамилия" />
    </div>

    <button type="submit">Зарегистрировать</button>
  </form>
</template>

<style lang="scss" scoped>
select {
  margin-bottom: 10px;
}
</style>
